#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sshtodevice.h"
#include <QIntValidator>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lineEdit_ip->setValidator(new QRegExpValidator(QRegExp("\\b(?:(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.){3}(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\b")));
    ui->lineEdit_ip->setText(m_param.IP);
    ui->lineEdit_port->setValidator(new QIntValidator(0, 65535, this));
    ui->lineEdit_port->setText(QString::number(m_param.Port));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionSSH_triggered()
{
    sshToDevice* ssh = new sshToDevice(ui->lineEdit_ip->text());
    ssh->show();
}


void MainWindow::on_pushButton_clicked()
{
    m_param.IP = ui->lineEdit_ip->text();
    m_param.Port = ui->lineEdit_port->text().toInt();
    m_param.SetConfig();
}
