#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sshtodevice.h"
#include <QIntValidator>
#include <QMessageBox>

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
}

MainWindow::~MainWindow()
{
    m_param.SetConfig();
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
    }
    else
    {
        m_socket.BreakOffConnect();
        ui->pushButton->setText("连接");
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
    m_socket.SendData(ui->lineEdit_send->text() + "\r\n");
    ui->lineEdit_send->clear();
}

void MainWindow::getSocketDataShow(QString data)
{
    ui->textBrowser_recv->append(data);
    if (data == "Connect Break Off")
    {
        QMessageBox::information(NULL, "错误", "设备异常掉线", QMessageBox::Yes);
        on_pushButton_clicked();
    }
}

void MainWindow::changeStatusOfUI(bool value)
{
    ui->tabWidget->setEnabled(value);
}