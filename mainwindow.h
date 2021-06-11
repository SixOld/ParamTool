#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ParamSave.h"
#include "SocketOperation.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionSSH_triggered();
    void on_pushButton_clicked();
    void saveSshPasswd(QString user, QString passwd);
    void setColorValue(int value);
    void on_lineEdit_send_returnPressed();
    void getSocketDataShow(QString data);
    void setColorText(QString value);

private:
    void initColorSlider(void);
    C_ParamSave m_param;
    Ui::MainWindow *ui;
    C_SocketOperation m_socket;
};
#endif // MAINWINDOW_H
