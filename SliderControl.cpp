#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <SocketOperation.h>

void MainWindow::initColorSlider(void)
{
	QObjectList objects = ui->tabWidgetPageColor->children();
	for (size_t ki = 0; ki < objects.size(); ki++)
	{
		if (objects[ki]->objectName().startsWith("horizontalSlider"))
		{
			QSlider* slider = qobject_cast<QSlider*>(objects[ki]);
			slider->setRange(0, 255);
			connect(slider, &QSlider::valueChanged, this, &MainWindow::setColorValue);;

		}
		else if (objects[ki]->objectName().startsWith("lineEdit"))
		{
			QLineEdit* lineEdit = qobject_cast<QLineEdit*>(objects[ki]);
			lineEdit->setValidator(new QIntValidator(0, 255, this));
			connect(lineEdit, &QLineEdit::textChanged, this, &MainWindow::setColorText);
		}
	}
	ui->horizontalSlider_color->setRange(0, 1);
	ui->lineEdit_color->setValidator(new QIntValidator(0, 1, this));


}

void MainWindow::setColorValue(int value)
{
	QSlider* slider = qobject_cast<QSlider*>(sender());
	QObjectList list = slider->parent()->children();
	QString objectName = QObject::sender()->objectName().split("_").last();
	for (size_t ki = 0; ki < list.size(); ki++)
	{
		if (list[ki]->objectName().contains(objectName) && list[ki]->objectName() != slider->objectName())
		{
			qobject_cast<QLineEdit*>(list[ki])->setText(QString::number(value));
		}
	}
	S_SendProtocol sendData = {};
	sendData.HeadStart	= 0xaa;
	sendData.HeadEnd	= 0xbb;
	strcpy((char*)sendData.DataName, objectName.toLatin1().data());
	memcpy(sendData.value, &value, sizeof(value));
	sendData.Length = sizeof(sendData);
	m_socket.SendData(sendData);
}

void MainWindow::setColorText(QString value)
{
	QLineEdit* lineEdit = qobject_cast<QLineEdit*>(sender());
	QObjectList list = lineEdit->parent()->children();
	QString objectName = QObject::sender()->objectName().split("_").last();
	for (size_t ki = 0; ki < list.size(); ki++)
	{
		if (list[ki]->objectName().contains(objectName) && list[ki]->objectName() != lineEdit->objectName())
		{
			qobject_cast<QSlider*>(list[ki])->setValue(value.toInt());
		}
	}
	S_SendProtocol sendData = {};
	sendData.HeadStart = 0xaa;
	sendData.HeadEnd = 0xbb;
	strcpy((char*)sendData.DataName, objectName.toLatin1().data());
	memcpy(sendData.value, &value, sizeof(value));
	sendData.Length = sizeof(sendData);
	m_socket.SendData(sendData);
}