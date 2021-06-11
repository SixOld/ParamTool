#include "SocketOperation.h"

C_SocketOperation::C_SocketOperation()
{
	m_tcp = new QTcpSocket();
	connect(m_tcp, &QTcpSocket::readyRead, this, &C_SocketOperation::socketReadData);
	connect(m_tcp, &QTcpSocket::disconnected, this, &C_SocketOperation::socketDisconnected);

	m_udpImage = new QUdpSocket();
	m_udpImage->bind(QHostAddress("127.0.0.1"), UDP_IMAGE_PORT);
	connect(m_udpImage, &QUdpSocket::readyRead, this, &C_SocketOperation::imageRecvice);
}

C_SocketOperation::~C_SocketOperation()
{
	if (m_tcp != nullptr)
	{
		delete m_tcp;
	}
}

int32_t C_SocketOperation::ConnectToService(QString ip, int port)
{
	m_tcp->abort();
	m_tcp->connectToHost(ip, port);

	if (!m_tcp->waitForConnected(10000))
	{
		qDebug() << "Connection failed!";
		return -1;
	}
	return 0;
}

int32_t C_SocketOperation::BreakOffConnect()
{
	m_tcp->disconnectFromHost();
	return 0;
}

int32_t C_SocketOperation::SendData(QString data)
{
	//读取缓冲区数据
	if (m_tcp->write(data.toLatin1()) > 0)
	{
		m_tcp->flush();
		return 0;
	}
	return -1;
}

int32_t C_SocketOperation::SendData(S_SendProtocol data)
{
	//读取缓冲区数据
	if (m_tcp->write((char*)&data, sizeof(data)) > 0)
	{
		m_tcp->flush();
		return 0;
	}
	return -1;
}

void C_SocketOperation::socketReadData()
{
	//读取缓冲区数据
	QByteArray buffer = m_tcp->readAll();
	S_SendProtocol* recvData = (S_SendProtocol*)buffer.data();
	QString str = QString(buffer);
	if (recvData->Length == sizeof(S_SendProtocol))
	{
		int32_t value = 0;
		memcpy(&value, recvData->value, sizeof(value));
		str = QString("Protocol, DataName: %1, Value: %2").arg(QString((char*)recvData->DataName)).arg(value);
	}
	emit sigSocketRecvData(str);
}

void C_SocketOperation::socketDisconnected()
{
	emit sigSocketRecvData(QString("Connect Break Off"));
}

void C_SocketOperation::imageRecvice()
{
	QByteArray buffer;

	while (m_udpImage->hasPendingDatagrams())
	{
		buffer.resize(m_udpImage->pendingDatagramSize());
		m_udpImage->readDatagram(buffer.data(), buffer.size());
		emit sigSocketRecvData(buffer);
	}
}