#include "ParamSave.h"
#include <QFile>
#include <QJsonDocument>
#include <QDebug>
#include <QJsonObject>

C_ParamSave::C_ParamSave()
{
    IP = "";
    UserName = "";
    PassWord = "";
    Port = 6677;
    getConfig();
}

/************************************
 * Function:        getConfig
 * Description:     获取设置保存的Config文件
 * Access Level:    private
 * Input:           N/A
 * Output:          N/A
 * Return:          N/A
 ************************************/
void C_ParamSave::getConfig(void)
{
    QFile file("./config.json");
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "File open error";
        return;
    }
    QByteArray data = file.readAll();
    file.close();
    QJsonDocument doc = QJsonDocument::fromJson(data);
    if (!doc.isObject())
    {
        qDebug() << "Json Error";
        return;
    }
    QJsonObject obj = doc.object();
    IP = obj.value("IP").toString();
    Port = obj.value("Port").toInt();
    UserName = obj.value("UserName").toString();
    PassWord = obj.value("PassWord").toString();
}

/************************************
 * Function:        setConfig
 * Description:     将设置保存到json文件
 * Access Level:    private
 * Input:           N/A
 * Output:          N/A
 * Return:          N/A
 ************************************/
void C_ParamSave::SetConfig(void)
{
    QJsonObject obj;
    obj.insert("IP", IP);
    obj.insert("Port", Port);
    obj.insert("UserName", UserName);
    obj.insert("PassWord", PassWord);
    QJsonDocument doc(obj);
    QFile file("./config.json");
    file.open(QIODevice::WriteOnly);
    file.write(doc.toJson());
    file.close();
}
