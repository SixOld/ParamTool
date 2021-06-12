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

    m_pTimer = new QTimer(this);
    connect(m_pTimer, &QTimer::timeout, this, &MainWindow::handleTimeout);
    m_pTimer->setInterval(10);
    m_pTimer->start();

    connect(&m_socket, &C_SocketOperation::sigSocketSetSliderValue, this, &MainWindow::changeSliderValue);
}

MainWindow::~MainWindow()
{
    m_param.SetConfig();
    delete m_pTimer;
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
        changeStatusOfUI(true);
        ui->textBrowser_recv->clear();
        S_SendProtocol sendData = {};
        sendData.HeadStart = 0xaa;
        sendData.HeadEnd = 0xbb;
        sendData.Length = sizeof(sendData);
        sendData.Cmd = TCP_GET_COLOR;
        m_socket.SendData(sendData);

        //QMap<QString, uint8_t>::iterator it; //遍历map  
        //for (it = m_cmdMap.begin(); it != m_cmdMap.end(); ++it) 
        //{
        //    sendData.Cmd = it.value() + 1;
        //    m_socket.SendData(sendData);
        //    cv::waitKey(10);
        //}
    }
    else
    {
        ui->pushButton->setText("连接");
        m_socket.BreakOffConnect();
        ui->lineEdit_ip->setEnabled(true);
        ui->lineEdit_port->setEnabled(true);
        ui->lineEdit_send->setEnabled(false);
        changeStatusOfUI(false);
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
    ui->lineEdit_send->clear();
}

void MainWindow::getSocketDataShow(QString data)
{
    ui->textBrowser_recv->append(data);
    if (data == "Connect Break Off" && ui->pushButton->text() == "断开")
    {
        QMessageBox::information(NULL, "错误", "设备异常掉线", QMessageBox::Yes);
        on_pushButton_clicked();
    }
}

void MainWindow::getSocketImageShow(char* data, int length)
{
    if (m_showFlagImage)
    {
        cv::Mat img_decode;
        std::vector<uchar> data_encode;
        data_encode.insert(data_encode.end(), data, data + length);
        img_decode = cv::imdecode(data_encode, CV_LOAD_IMAGE_COLOR);
        cv::cvtColor(img_decode, img_decode, CV_BGR2RGB);//BGR convert to RGB
        cv::resize(img_decode, img_decode, cv::Size(ui->Image_frame->width(), ui->Image_frame->height()), 0, 0, cv::INTER_NEAREST);
        QImage Qtemp = QImage((const unsigned char*)(img_decode.data), img_decode.cols, img_decode.rows, img_decode.step, QImage::Format_RGB888);
        ui->Image_frame->setPixmap(QPixmap::fromImage(Qtemp));
        ui->Image_frame->show();
        m_showFlagImage = false;
    }
}

void MainWindow::getSocketBinaryShow(char* data, int length)
{
    if (m_showFlagBinary)
    {
        cv::Mat img_decode;
        std::vector<uchar> data_encode;
        data_encode.insert(data_encode.end(), data, data + length);
        img_decode = cv::imdecode(data_encode, CV_LOAD_IMAGE_COLOR);
        cv::cvtColor(img_decode, img_decode, CV_BGR2RGB);//BGR convert to RGB
        cv::resize(img_decode, img_decode, cv::Size(ui->Image_binary->width(), ui->Image_binary->height()), 0, 0, cv::INTER_NEAREST);
        QImage Qtemp = QImage((const unsigned char*)(img_decode.data), img_decode.cols, img_decode.rows, img_decode.step, QImage::Format_RGB888);
        ui->Image_binary->setPixmap(QPixmap::fromImage(Qtemp));
        ui->Image_binary->show();
        m_showFlagBinary = false;
    }
}

void MainWindow::changeStatusOfUI(bool value)
{
    ui->tabWidget->setEnabled(value);
}

void MainWindow::handleTimeout()
{
    m_showFlagBinary = true;
    m_showFlagImage = true;
}