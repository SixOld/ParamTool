#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ParamSave.h"
#include "SocketOperation.h"
#include <QTimer>
#include <QMutex>

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
    void handleDebugTimeout();
    void changeSliderValue(uint8_t cmd, int value);
    void setDebugOutput(int value);

private:
    void initColorSlider(void);
    void changeStatusOfUI(bool value);
    void cmdMapInit();
    void initCheckBox();
    Ui::MainWindow *ui;
    QTimer* mp_imageTimer = nullptr;
    QTimer* mp_debugTimer = nullptr;
    C_ParamSave m_param;
    C_SocketOperation m_socket;
    QMap<QString, uint8_t> m_cmdMap; //定义一个QMap对象
    QMutex imageMutex;
    QMutex binaryMutex;
    QString debugInfo;
    uint8_t imageCount;

    std::vector<std::vector<uchar>> imageEncode;
    std::vector<std::vector<uchar>> imageEncodeTmp;    
    uint8_t binaryCount;
    std::vector<std::vector<uchar>> binaryEncode;
    std::vector<std::vector<uchar>> binaryEncodeTmp;    

};
#endif // MAINWINDOW_H
