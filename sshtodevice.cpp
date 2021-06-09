#include "sshtodevice.h"
#include "ui_sshtodevice.h"

sshToDevice::sshToDevice(QString ip, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::sshToDevice)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
    m_ip = ip;
    QSsh::SshConnectionParameters argParameters;
    argParameters.host = ip;
    argParameters.userName = "root";
    argParameters.password = "hik_linux";
    argParameters.port = 22;
    argParameters.timeout = 5;
    argParameters.authenticationType = QSsh::SshConnectionParameters::AuthenticationTypePassword;
    if (m_pSshSocket == nullptr) {
        m_pSshSocket = new QSsh::SshConnection(argParameters);
        connect(m_pSshSocket, SIGNAL(connected()), SLOT(handleConnected()));
        connect(m_pSshSocket, SIGNAL(error(QSsh::SshError)), SLOT(slotSshConnectError(QSsh::SshError)));
    }
    m_pSshSocket->connectToHost();
}

sshToDevice::~sshToDevice()
{
    if (m_pSshSocket != nullptr)
    {
        delete m_pSshSocket;
    }
    delete ui;
}

void sshToDevice::slotSshConnectError(QSsh::SshError sshError)
{
    switch (sshError) {
    case QSsh::SshNoError:
        qDebug() << "slotSshConnectError SshNoError";
        break;
    case QSsh::SshSocketError:
        qDebug() << "slotSshConnectError SshSocketError"; //拔掉网线是这种错误
        break;
    case QSsh::SshTimeoutError:
        qDebug() << "slotSshConnectError SshTimeoutError";
        break;
    case QSsh::SshProtocolError:
        qDebug() << "slotSshConnectError SshProtocolError";
        break;
    case QSsh::SshHostKeyError:
        qDebug() << "slotSshConnectError SshHostKeyError";
        break;
    case QSsh::SshKeyFileError:
        qDebug() << "slotSshConnectError SshKeyFileError";
        break;
    case QSsh::SshAuthenticationError:
        qDebug() << "slotSshConnectError SshAuthenticationError";
        break;
    case QSsh::SshClosedByServerError:
        qDebug() << "slotSshConnectError SshClosedByServerError";
        break;
    case QSsh::SshInternalError:
        qDebug() << "slotSshConnectError SshInternalError";
        break;
    default:
        break;
    }

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
//    if(strRecv.contains("password for")){
//        m_shell->write(m_strPwd.toLatin1().data());
//    }

    if(!strRecv.isEmpty()) //过滤空行
    {
        ui->textBrowser_Recv->append(strRecv);
    }
}

void sshToDevice::on_lineEdit_Send_returnPressed()
{
    m_shell->write((ui->lineEdit_Send->text() + "\n").toUtf8());
    ui->lineEdit_Send->clear();
}
