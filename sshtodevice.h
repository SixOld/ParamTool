#ifndef SSHTODEVICE_H
#define SSHTODEVICE_H

#include <QWidget>
#include <ssh/sshconnection.h>
#include <ssh/sshremoteprocess.h>
#include "SshPasswdIn.h"

#ifdef WIN32
#pragma execution_character_set("utf-8")
#endif

namespace Ui {
class sshToDevice;
}

class sshToDevice : public QWidget
{
    Q_OBJECT

public:
    explicit sshToDevice(QString ip, QString user, QString passwd, QWidget *parent = nullptr);
    ~sshToDevice();

private:
    void startSsh();
    Ui::sshToDevice *ui;
    QSsh::SshConnection *m_pSshSocket = nullptr;
    QSharedPointer<QSsh::SshRemoteProcess> m_shell;
    QSsh::SshConnectionParameters m_argParameters;

private slots:
    void handleConnected();
    void handleShellStarted();
    void handleRemoteStderr();
    void slotDataReceived();
    void slotSshConnectError(QSsh::SshError sshError);
    void on_lineEdit_Send_returnPressed();
    void SaveSshPasswd(QString user, QString passwd);

signals:
    void sigSaveSshPasswd(QString user, QString passwd);

};

#endif // SSHTODEVICE_H
