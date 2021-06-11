#ifndef SOCKET_OPERATION_H
#define SOCKET_OPERATION_H

#include <QTcpSocket>
#include <QString>
#include <QObject>

typedef struct 
{
	uint8_t		HeadStart;
	uint8_t		HeadEnd;
	uint8_t		DataName[128];
	uint8_t		value[4];
	uint32_t	Length;
}S_SendProtocol;

class C_SocketOperation : public QObject
{
	Q_OBJECT
public:
	C_SocketOperation();
	~C_SocketOperation();
	int32_t ConnectToService(QString ip, int port);
	int32_t BreakOffConnect();
	int32_t SendData(QString data);
	int32_t SendData(S_SendProtocol data);

private:
	QTcpSocket* m_socket = nullptr;

private slots:
	void socketReadData();
	void socketDisconnected();

signals:
	void sigSocketRecvData(QString text);
};

#endif
