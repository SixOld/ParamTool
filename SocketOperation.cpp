#include "SocketOperation.h"

C_SocketOperation::C_SocketOperation()
{
	m_socket = new QTcpSocket();
	QObject::connect(m_socket, SIGNAL(QTcpSocket::readyRead()), this, SLOT(socket_Read_Data));
	QObject::connect(m_socket, SIGNAL(QTcpSocket::disconnected()), this, SLOT(socket_Disconnected));
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

void C_SocketOperation::socket_Read_Data()
{
	//读取缓冲区数据
	QByteArray buffer = m_socket->readAll();

}

void C_SocketOperation::socket_Disconnected()
{

}