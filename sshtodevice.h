#ifndef SSHTODEVICE_H
#define SSHTODEVICE_H

#include <QWidget>
#include <ssh/sshconnection.h>
#include <ssh/sshremoteprocess.h>

namespace Ui {
class sshToDevice;
}

class sshToDevice : public QWidget
{
    Q_OBJECT

public:
    explicit sshToDevice(QString ip, QWidget *parent = nullptr);
    ~sshToDevice();

private:
    Ui::sshToDevice *ui;
    QSsh::SshConnection *m_pSshSocket = nullptr;
    QSharedPointer<QSsh::SshRemoteProcess> m_shell;
    QString m_ip;
    int m_port;

private slots:
    void handleConnected();
    void handleShellStarted();
    void handleRemoteStderr();
    void slotDataReceived();
    void slotSshConnectError(QSsh::SshError sshError);
    void on_lineEdit_Send_returnPressed();
};

#endif // SSHTODEVICE_H
