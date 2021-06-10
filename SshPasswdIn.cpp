#include "SshPasswdIn.h"
#include "ui_SshPasswdIn.h"

C_SshPasswdIn::C_SshPasswdIn(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::C_SshPasswdIn)
{
    ui->setupUi(this);    
    setWindowModality(Qt::ApplicationModal);   // 界面打开后阻塞父界面
    setAttribute(Qt::WA_DeleteOnClose);
    ui->lineEdit_passwd->setEchoMode(QLineEdit::Password);
}

C_SshPasswdIn::~C_SshPasswdIn()
{

    delete ui;
}

void C_SshPasswdIn::on_lineEdit_passwd_returnPressed()
{
    on_pushButton_yes_clicked();
}

void C_SshPasswdIn::on_pushButton_yes_clicked()
{
    emit sigSaveSshPasswd(ui->lineEdit_user->text(), ui->lineEdit_passwd->text());
    close();
}

void C_SshPasswdIn::on_pushButton_cacel_clicked()
{
    close();
}
