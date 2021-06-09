#include "sshtodevice.h"
#include "ui_sshtodevice.h"
#include <QMessageBox>

sshToDevice::sshToDevice(QString ip, QString user, QString passwd, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::sshToDevice)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);    
    m_argParameters.host = ip;
    m_argParameters.userName = user;
    m_argParameters.password = passwd;
    m_argParameters.port = 22;
    m_argParameters.timeout = 5;
    m_argParameters.authenticationType = QSsh::SshConnectionParameters::AuthenticationTypePassword;
    startSsh();
}

sshToDevice::~sshToDevice()
{
    if (m_pSshSocket != nullptr)
    {
        delete m_pSshSocket;
    }
    delete ui;
}

void sshToDevice::startSsh()
{
    if (m_pSshSocket != nullptr)
    {
        delete m_pSshSocket;
        m_pSshSocket = nullptr;
    }
    m_pSshSocket = new QSsh::SshConnection(m_argParameters);
    connect(m_pSshSocket, SIGNAL(connected()), SLOT(handleConnected()));
    connect(m_pSshSocket, SIGNAL(error(QSsh::SshError)), SLOT(slotSshConnectError(QSsh::SshError)));
    m_pSshSocket->connectToHost();

}

void sshToDevice::slotSshConnectError(QSsh::SshError sshError)
{
    switch (sshError) 
    {
        case QSsh::SshNoError:
            qDebug() << "slotSshConnectError SshNoError";
            QMessageBox::information(NULL, "´íÎó", "Éè±¸Á¬½ÓÊ§°Ü", QMessageBox::Yes);
            break;
        case QSsh::SshSocketError:
            qDebug() << "slotSshConnectError SshSocketError"; //°ÎµôÍøÏßÊÇÕâÖÖ´íÎó
            QMessageBox::information(NULL, "´íÎó", "Éè±¸µôÏß", QMessageBox::Yes);
            break;
        case QSsh::SshTimeoutError:
            qDebug() << "slotSshConnectError SshTimeoutError";
            QMessageBox::information(NULL, "´íÎó", "Á¬½Ó³¬Ê±", QMessageBox::Yes);
            break;
        case QSsh::SshProtocolError:
            qDebug() << "slotSshConnectError SshProtocolError";
            QMessageBox::information(NULL, "´íÎó", "SSHÐ­Òé´íÎó", QMessageBox::Yes);
            break;
        case QSsh::SshHostKeyError:
        {
            qDebug() << "slotSshConnectError SshHostKeyError";
            QMessageBox::information(NULL, "´íÎó", "SSHÕËºÅÃÜÂë´íÎó", QMessageBox::Yes);
            C_SshPasswdIn* inputSshPasswd = new C_SshPasswdIn;
            connect(inputSshPasswd, SIGNAL(sigSaveSshPasswd), SLOT(SaveSshPasswd));
            inputSshPasswd->show();
            return;
            break;
        }
        case QSsh::SshKeyFileError:
            qDebug() << "slotSshConnectError SshKeyFileError";
            QMessageBox::information(NULL, "´íÎó", "ÃÜÔ¿ÎÄ¼þ´íÎó", QMessageBox::Yes);
            break;
        case QSsh::SshAuthenticationError:
        {
            qDebug() << "slotSshConnectError SshAuthenticationError";
            QMessageBox::information(NULL, "´íÎó", "SSHÕËºÅÃÜÂë´íÎó", QMessageBox::Yes);
            C_SshPasswdIn* inputSshPasswd = new C_SshPasswdIn;
            connect(inputSshPasswd, SIGNAL(sigSaveSshPasswd(QString, QString)), SLOT(SaveSshPasswd(QString, QString)));
            inputSshPasswd->show();
            return;
            break;
        }
        case QSsh::SshClosedByServerError:
            qDebug() << "slotSshConnectError SshClosedByServerError";
            QMessageBox::information(NULL, "´íÎó", "Éè±¸¹Ø±ÕÁ¬½Ó", QMessageBox::Yes);
            break;
        case QSsh::SshInternalError:
            qDebug() << "slotSshConnectError SshInternalError";
            QMessageBox::information(NULL, "´íÎó", "ÍøÂç´íÎó", QMessageBox::Yes);
            break;
        default:
            break;
    }
    close();
}

void sshToDevice::handleConnected()
{
    m_shell = m_pSshSocket->createRemoteShell();
    connect(m_shell.data(), SIGNAL(started()), SLOT(handleShellStarted()));
    connect(m_shell.data(), SIGNAL(readyReadStandardOutput()), SLOT(slotDataReceived()));
    connect(m_shell.data(), SIGNAL(readyReadStandardError()), SLOT(handleRemoteStderr()));
    m_shell->start();
}

void sshToDevice::handleShellStarted()
{
    qDebug() << "Connect success";
}

void sshToDevice::handleRemoteStderr()
{
    qDebug() << "shell standard err" << QString::fromLocal8Bit(m_shell->readAllStandardError());
}

void sshToDevice::slotDataReceived()
{
    QByteArray byteRecv = m_shell->readAllStandardOutput();
    QString strRecv = (byteRecv);
    QRegExp re("\\x1b\\[[0-9]+(?:;[0-9]+){0,2}m");
    strRecv.replace(re, "");

    if(!strRecv.isEmpty()) //¹ýÂË¿ÕÐÐ
    {
        ui->textBrowser_Recv->append(strRecv);
    }
}

void sshToDevice::on_lineEdit_Send_returnPressed()
{
    m_shell->write((ui->lineEdit_Send->text() + "\n").toUtf8());
    ui->lineEdit_Send->clear();
}

void sshToDevice::SaveSshPasswd(QString user, QString passwd)
{
    emit sigSaveSshPasswd(user, passwd);
    m_argParameters.userName = user;
    m_argParameters.password = passwd;
    startSsh();
}