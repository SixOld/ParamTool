#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sshtodevice.h"
#include <QIntValidator>
#include <QMessageBox>
#include <opencv.hpp>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lineEdit_ip->setValidator(new QRegExpValidator(QRegExp("\\b(?:(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.){3}(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\b")));
    ui->lineEdit_ip->setText(m_param.IP);
    ui->lineEdit_port->setValidator(new QIntValidator(0, 65535, this));
    ui->lineEdit_port->setText(QString::number(m_param.Port));
    ui->lineEdit_send->setEnabled(false);
    initColorSlider();
    changeStatusOfUI(false);
    connect(&m_socket, &C_SocketOperation::sigSocketRecvData, this, &MainWindow::getSocketDataShow);
    connect(&m_socket, &C_SocketOperation::sigSocketRecvImage, this, &MainWindow::getSocketImageShow);
    connect(&m_socket, &C_SocketOperation::sigSocketRecvBinary, this, &MainWindow::getSocketBinaryShow);

    mp_imageTimer = new QTimer(this);
    connect(mp_imageTimer, &QTimer::timeout, this, &MainWindow::handleTimeout);
    mp_imageTimer->setInterval(20);
    mp_imageTimer->start();

    mp_debugTimer = new QTimer(this);
    connect(mp_debugTimer, &QTimer::timeout, this, &MainWindow::handleDebugTimeout);
    mp_debugTimer->setInterval(100);

    connect(&m_socket, &C_SocketOperation::sigSocketSetSliderValue, this, &MainWindow::changeSliderValue);
}

MainWindow::~MainWindow()
{
    if (ui->pushButton->text() == "断开")
    {
        on_pushButton_clicked();
    }
    m_param.SetConfig();
    delete mp_imageTimer;
    delete ui;
}

void MainWindow::on_actionSSH_triggered()
{
    sshToDevice* ssh = new sshToDevice(ui->lineEdit_ip->text(), m_param.UserName, m_param.PassWord);
    ssh->show();
    connect(ssh, SIGNAL(sigSaveSshPasswd(QString, QString)), SLOT(saveSshPasswd(QString, QString)));
}


void MainWindow::on_pushButton_clicked()
{
    if (ui->pushButton->text() == "连接")
    {
        m_param.IP = ui->lineEdit_ip->text();
        m_param.Port = ui->lineEdit_port->text().toInt();
        m_param.SetConfig();

        if (m_socket.ConnectToService(m_param.IP, m_param.Port) < 0)
        {
            QMessageBox::information(NULL, "错误", "设备连接失败", QMessageBox::Yes);
            return;
        }
        ui->pushButton->setText("断开");
        ui->lineEdit_ip->setEnabled(false);
        ui->lineEdit_port->setEnabled(false);
        ui->lineEdit_send->setEnabled(true);
        ui->textBrowser_recv->clear();
        S_SendProtocol sendData = {};
        sendData.HeadStart = 0xaa;
        sendData.HeadEnd = 0xbb;
        sendData.Length = sizeof(sendData);
        sendData.Cmd = TCP_GET_ALL;
        m_socket.SendData(sendData);
        mp_debugTimer->start();
    }
    else
    {
        ui->pushButton->setText("连接");
        m_socket.BreakOffConnect();
        ui->lineEdit_ip->setEnabled(true);
        ui->lineEdit_port->setEnabled(true);
        ui->lineEdit_send->setEnabled(false);
        changeStatusOfUI(false);
        mp_debugTimer->stop();
    }
}

void MainWindow::saveSshPasswd(QString user, QString passwd)
{
    m_param.UserName = user;
    m_param.PassWord = passwd;
    m_param.SetConfig();
}

void MainWindow::on_lineEdit_send_returnPressed()
{
    m_socket.SendData(ui->lineEdit_send->text());
    if (ui->lineEdit_send->text() == "debug")
    {
        S_SendProtocol sendData = {};
        sendData.HeadStart = 0xaa;
        sendData.HeadEnd = 0xbb;
        sendData.Length = sizeof(sendData);
        sendData.Cmd = TCP_SET_COLOR;
        m_socket.SendData(sendData);
        changeStatusOfUI(true);
    }
    else if (ui->lineEdit_send->text() == "release")
    {
        changeStatusOfUI(false);
    }
    ui->lineEdit_send->clear();
}

void MainWindow::getSocketDataShow(QString data)
{
    debugInfo.append(data);
    debugInfo.append("\n");
    if (data == "Connect Break Off" && ui->pushButton->text() == "断开")
    {
        QMessageBox::information(NULL, "错误", "设备异常掉线", QMessageBox::Yes);
        on_pushButton_clicked();
    }
}

void MainWindow::getSocketImageShow(char* data, int length)
{
    imageMutex.lock();

    if (data[0] == '?' && data[1] == imageCount)
    {
        std::vector<uchar> tmpData;
        tmpData.insert(tmpData.end(), data + 2, data + length);
        imageEncodeTmp.push_back(tmpData);
        if (imageCount == UDP_IMAGE_SPLIT_SIZE - 1)
        {
            imageEncode.clear();
            imageEncode.swap(imageEncodeTmp);
            imageCount = 0;
        }
        else
        {
            imageCount++;
        }
    }
    else
    {
        imageCount = 0;
    }
    imageMutex.unlock();
}

void MainWindow::getSocketBinaryShow(char* data, int length)
{
    binaryMutex.lock();

    if (data[0] == '?' && data[1] == binaryCount)
    {
        std::vector<uchar> tmpData;
        tmpData.insert(tmpData.end(), data + 2, data + length);
        binaryEncodeTmp.push_back(tmpData);
        if (binaryCount == UDP_BINARY_SPLIT_SIZE - 1)
        {
            binaryEncode.clear();
            binaryEncode.swap(binaryEncodeTmp);
            binaryCount = 0;
        }
        else
        {
            binaryCount++;
        }
    }
    else
    {
        binaryCount = 0;
    }
    binaryMutex.unlock();
}

void MainWindow::changeStatusOfUI(bool value)
{
    ui->tabWidget->setEnabled(value);
}

void MainWindow::handleTimeout()
{
    static int count;

    if (m_socket.Recvicing)
    {
        if (count++ < 50)
        {
            m_socket.Recvicing = false;
            return;
        }
    }
    else
    {
        count = 0;
    }
    imageMutex.lock();

    /* 解码 */
    if (imageEncode.size() == UDP_IMAGE_SPLIT_SIZE)
    {
        cv::Mat img_decode;
        for (size_t ki = 0; ki < imageEncode.size(); ki++)
        {
            cv::Mat tmpImage = cv::imdecode(imageEncode.at(ki), CV_LOAD_IMAGE_COLOR);
            if (ki == 0)
            {
                img_decode = tmpImage;
            }
            else
            {
                cv::vconcat(img_decode, tmpImage, img_decode);
            }
        }
        cv::cvtColor(img_decode, img_decode, CV_BGR2RGB);//BGR convert to RGB
        cv::resize(img_decode, img_decode, cv::Size(ui->Image_frame->width(), ui->Image_frame->height()), 0, 0, cv::INTER_NEAREST);
        QImage Qtemp = QImage((const unsigned char*)(img_decode.data), img_decode.cols, img_decode.rows, img_decode.step, QImage::Format_RGB888);
        ui->Image_frame->setPixmap(QPixmap::fromImage(Qtemp));
        ui->Image_frame->show();
        imageEncode.clear();
    }
    imageMutex.unlock();
    binaryMutex.lock();

    if (binaryEncode.size() == UDP_BINARY_SPLIT_SIZE)
    {
        cv::Mat img_decode;
        for (size_t ki = 0; ki < binaryEncode.size(); ki++)
        {
            cv::Mat tmpbinary = cv::imdecode(binaryEncode.at(ki), CV_LOAD_IMAGE_COLOR);
            if (ki == 0)
            {
                img_decode = tmpbinary;
            }
            else
            {
                cv::vconcat(img_decode, tmpbinary, img_decode);
            }
        }
        cv::cvtColor(img_decode, img_decode, CV_BGR2RGB);//BGR convert to RGB
        cv::resize(img_decode, img_decode, cv::Size(ui->Image_binary->width(), ui->Image_binary->height()), 0, 0, cv::INTER_NEAREST);
        QImage Qtemp = QImage((const unsigned char*)(img_decode.data), img_decode.cols, img_decode.rows, img_decode.step, QImage::Format_RGB888);
        ui->Image_binary->setPixmap(QPixmap::fromImage(Qtemp));
        ui->Image_binary->show();
        binaryEncode.clear();
    }
    binaryMutex.unlock();
}

void MainWindow::handleDebugTimeout()
{
    if (debugInfo != "")
    {
        ui->textBrowser_recv->append(debugInfo);
        debugInfo = "";
    }
}