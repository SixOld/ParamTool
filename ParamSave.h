#ifndef PARAMSAVE_H
#define PARAMSAVE_H

#include <QString>

class C_ParamSave
{
public:
    C_ParamSave();
    void SetConfig(void);
    QString IP;
    int Port;
    QString UserName;
    QString PassWord;
private:
    void getConfig(void);

};

#endif // PARAMSAVE_H
