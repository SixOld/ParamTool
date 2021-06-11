#include "SocketOperation.h"

C_SocketOperation::C_SocketOperation()
{
	m_socket = new QTcpSocket();
	QObject::connect(m_socket, &QTcpSocket::readyRead, this, &C_SocketOperation::socketReadData);
	QObject::connect(m_socket, &QTcpSocket::disconnected, this, &C_SocketOperation::socketDisconnected);
}

C_SocketOperation::~C_SocketOperation()
{
	if (m_socket != nullptr)
	{
		delete m_socket;
	}
}

int32_t C_SocketOperation::ConnectToService(QString ip, int port)
{
	m_socket->abort();
	m_socket->connectToHost(ip, port);

	if (!m_socket->waitForConnected(10000))
	{
		qDebug() << "Connection failed!";
		return -1;
	}
	return 0;
}

int32_t C_SocketOperation::BreakOffConnect()
{
	m_socket->disconnectFromHost();
	return 0;
}

int32_t C_SocketOperation::SendData(QString data)
{
	//读取缓冲区数据
	if (m_socket->write(data.toLatin1()) > 0)
	{
		m_socket->flush();
		return 0;
	}
	return -1;
}

int32_t C_SocketOperation::SendData(S_SendProtocol data)
{
	//读取缓冲区数据
	if (m_socket->write((char*)&data, sizeof(data)) > 0)
	{
		m_socket->flush();
		return 0;
	}
	return -1;
}

void C_SocketOperation::socketReadData()
{
	//读取缓冲区数据
	QByteArray buffer = m_socket->readAll();
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
	emit sigSocketRecvData(QString("Connect Break"));
}