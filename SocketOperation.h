#ifndef SOCKET_OPERATION_H
#define SOCKET_OPERATION_H

#include <QTcpSocket>
#include <QUdpSocket>
#include <QString>
#include <QObject>

#define UDP_DEBUG_PORT	7788
#define UDP_IMAGE_PORT	8899
#define UDP_BINARY_PORT	9900
#define UDP_RECV_IP		"192.0.0.128"

enum
{
	/* 颜色 */
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
	/* 灯条 */
	TCP_SET_LIGHT_ANGLE_MIN,
	TCP_GET_LIGHT_ANGLE_MIN,
	TCP_SET_LIGHT_ANGLE_MAX,
	TCP_GET_LIGHT_ANGLE_MAX,
	TCP_SET_LIGHT_AREA_MIN,
	TCP_GET_LIGHT_AREA_MIN,
	TCP_SET_LIGHT_AREA_MAX,
	TCP_GET_LIGHT_AREA_MAX,
	TCP_SET_LIGHT_PROP_MIN,
	TCP_GET_LIGHT_PROP_MIN,
	TCP_SET_LIGHT_PROP_MAX,
	TCP_GET_LIGHT_PROP_MAX,
	TCP_SET_LIGHT_ANGLE_DIFF,
	TCP_GET_LIGHT_ANGLE_DIFF,
	TCP_SET_LIGHT_AREA_DIFF,
	TCP_GET_LIGHT_AREA_DIFF,
	TCP_SET_LIGHT_LONG_PORP_AREA_DIFF_MIN,
	TCP_GET_LIGHT_LONG_PORP_AREA_DIFF_MIN,
	TCP_SET_LIGHT_LONG_PORP_AREA_DIFF_MAX,
	TCP_GET_LIGHT_LONG_PORP_AREA_DIFF_MAX,
	/* 装甲板 */
	TCP_SET_ARMOR_ANGLE_MIN,
	TCP_GET_ARMOR_ANGLE_MIN,
	TCP_SET_ARMOR_AREA_MIN,
	TCP_GET_ARMOR_AREA_MIN,
	TCP_SET_ARMOR_AREA_MAX,
	TCP_GET_ARMOR_AREA_MAX,
	TCP_SET_SMALL_ARMOR_PROP_MIN,
	TCP_GET_SMALL_ARMOR_PROP_MIN,
	TCP_SET_SMALL_ARMOR_PROP_MAX,
	TCP_GET_SMALL_ARMOR_PROP_MAX,
	TCP_SET_BIG_ARMOR_PROP_MIN,
	TCP_GET_BIG_ARMOR_PROP_MIN,
	TCP_SET_BIG_ARMOR_PROP_MAX,
	TCP_GET_BIG_ARMOR_PROP_MAX,
	TCP_SET_SMALL_DISTANCE_PARAM,
	TCP_GET_SMALL_DISTANCE_PARAM,
	TCP_SET_BIG_DISTANCE_PARAM,
	TCP_GET_BIG_DISTANCE_PARAM,
	/* 调试信息 */
	TCP_DEBUG_LIGHT_ANGLE,
	TCP_DEBUG_LIGHT_AREA,
	TCP_DEBUG_LIGHT_PROP,
	TCP_DEBUG_LIGHT_ANGLE_DIFF,
	TCP_DEBUG_LIGHT_AREA_DIFF,
	TCP_DEBUG_LIGHT_LONG_PROP,
	TCP_DEBUG_ARMOR_ANGLE,
	TCP_DEBUG_ARMOR_AREA,
	TCP_DEBUG_SMALL_ARMOR_PROP,
	TCP_DEBUG_BIG_ARMOR_PROP,
	TCP_DEBUG_SMALL_ARMOR_DISTANCE,
	TCP_DEBUG_BIG_ARMOR_DISTANCE,
	TCP_GET_ALL,
	TCP_NULL
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
	bool Recvicing = false;

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
