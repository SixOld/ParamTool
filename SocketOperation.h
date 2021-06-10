#ifndef SOCKET_OPERATION_H
#define SOCKET_OPERATION_H

#include <QTcpSocket>
#include <QString>
#include <QObject>

class C_SocketOperation : public QObject
{
	Q_OBJECT
public:
	C_SocketOperation();
	~C_SocketOperation();
	int32_t ConnectToService(QString ip, int port);
	int32_t BreakOffConnect();
private:
	QTcpSocket* m_socket = nullptr;

private slots:
	void socket_Read_Data();
	void socket_Disconnected();
};

#endif
