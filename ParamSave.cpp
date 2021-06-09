#include "ParamSave.h"
#include <QFile>
#include <QJsonDocument>
#include <QDebug>
#include <QJsonObject>

C_ParamSave::C_ParamSave()
{
    IP = "";
    Port = 6677;
    getConfig();
}

/************************************
 * Function:        getConfig
 * Description:     ��ȡ���ñ����Config�ļ�
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
}

/************************************
 * Function:        setConfig
 * Description:     �����ñ��浽json�ļ�
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
    QJsonDocument doc(obj);
    QFile file("./config.json");
    file.open(QIODevice::WriteOnly);
    file.write(doc.toJson());
    file.close();
}
