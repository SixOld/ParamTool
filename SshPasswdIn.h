#ifndef SSHPASSWDIN_H
#define SSHPASSWDIN_H

#include <QWidget>

namespace Ui {
class C_SshPasswdIn;
}

class C_SshPasswdIn : public QWidget
{
    Q_OBJECT

public:
    explicit C_SshPasswdIn(QWidget *parent = nullptr);
    ~C_SshPasswdIn();

private slots:
    void on_lineEdit_passwd_returnPressed();

    void on_pushButton_yes_clicked();

    void on_pushButton_cacel_clicked();
private:
    Ui::C_SshPasswdIn *ui;

signals:
    void sigSaveSshPasswd(QString user, QString passwd);
};

#endif // SSHPASSWDIN_H
