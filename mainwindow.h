#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ParamSave.h"
#include "SocketOperation.h"
#include <QTimer>

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
    void setColorText(QString value);
    void getSocketDataShow(QString data);
    void getSocketImageShow(char* data, int length);
    void getSocketBinaryShow(char* data, int length);
    void handleTimeout();
    void changeSliderValue(uint8_t cmd, int value);

private:
    void initColorSlider(void);
    void changeStatusOfUI(bool value);
    Ui::MainWindow *ui;
    QTimer* m_pTimer = nullptr;
    C_ParamSave m_param;
    C_SocketOperation m_socket;
    bool m_showFlagImage;
    bool m_showFlagBinary;
    QMap<QString, uint8_t> m_cmdMap; //定义一个QMap对象  

};
#endif // MAINWINDOW_H
