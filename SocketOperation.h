#ifndef SOCKET_OPERATION_H
#define SOCKET_OPERATION_H

#include <QTcpSocket>
#include <QUdpSocket>
#include <QString>
#include <QObject>

#define UDP_DEBUG_PORT	7788
#define UDP_IMAGE_PORT	8899
#define UDP_BINARY_PORT	9900
#define UDP_RECV_IP		"127.0.0.1"

enum
{
	TCP_SET_COLOR = 0x50,
	TCP_GET_COLOR,
	TCP_SET_H_MAX,
	TCP_GET_H_MAX,
	TCP_SET_H_MIN,
	TCP_GET_H_MIN,
	TCP_SET_S_MAX,
	TCP_GET_S_MAX,
	TCP_SET_S_MIN,
	TCP_GET_S_MIN,
	TCP_SET_V_MAX,
	TCP_GET_V_MAX,
	TCP_SET_V_MIN,
	TCP_GET_V_MIN,
};

typedef struct 
{
	uint8_t		HeadStart;
	uint8_t		HeadEnd;
	uint8_t		Cmd;
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
	QTcpSocket* m_tcp = nullptr;
	QUdpSocket* m_udpImage = nullptr;
	QUdpSocket* m_udpBinary = nullptr;
	QUdpSocket* m_udpDebug = nullptr;

private slots:
	void socketReadData();
	void socketDisconnected();
	void imageRecvice();
	void debugRecvice();

signals:
	void sigSocketRecvData(QString text);
	void sigSocketRecvImage(char* data, int length);
	void sigSocketRecvBinary(char* data, int length);
	void sigSocketSetSliderValue(uint8_t cmd, int value);
};

#endif
