#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "SocketOperation.h"
#include <QIntValidator>

void MainWindow::initColorSlider(void)
{
	QObjectList objects = ui->tabWidgetPageColor->children();
	for (size_t ki = 0; ki < objects.size(); ki++)
	{
		if (objects[ki]->objectName().startsWith("horizontalSlider"))
		{
			QSlider* slider = qobject_cast<QSlider*>(objects[ki]);
			slider->setRange(0, 255);
			connect(slider, &QSlider::valueChanged, this, &MainWindow::setColorValue);

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

	m_cmdMap.clear();
	m_cmdMap.insert("color", TCP_SET_COLOR);
	m_cmdMap.insert("hMax", TCP_SET_H_MAX);
	m_cmdMap.insert("hMin", TCP_SET_H_MIN);
	m_cmdMap.insert("sMax", TCP_SET_S_MAX);
	m_cmdMap.insert("sMin", TCP_SET_S_MIN);
	m_cmdMap.insert("vMax", TCP_SET_V_MAX);
	m_cmdMap.insert("vMin", TCP_SET_V_MIN);
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
	sendData.HeadEnd = 0xbb;
	sendData.Cmd = m_cmdMap[objectName];
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
}

void MainWindow::changeSliderValue(uint8_t cmd, int value)
{
	QObjectList objects;
	QString name;
	objects.append(ui->tabWidgetPageColor->children());
	objects.append(ui->tabWidgetPageShape->children());

	QMap<QString, uint8_t>::iterator it; //±éÀúmap  
	for (it = m_cmdMap.begin(); it != m_cmdMap.end(); ++it)
	{
		if (it.value() == cmd - 1)
		{
			name = it.key();
			break;
		}
	}
	if (name == "")
		return;
	for (size_t ki = 0; ki < objects.size(); ki++)
	{
		if (objects[ki]->objectName().endsWith(name))
		{
			QSlider* slider = qobject_cast<QSlider*>(objects[ki]);
			slider->setValue(value);
			break;
		}
	}
}