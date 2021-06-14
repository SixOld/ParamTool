#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "SocketOperation.h"
#include <QIntValidator>
#include <opencv.hpp>

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

	objects.clear();
	objects.append(ui->tabWidgetPageShape->children());
	objects.append(ui->tabWidgetPageArmor->children());

	for (size_t ki = 0; ki < objects.size(); ki++)
	{
		if (objects[ki]->objectName().startsWith("horizontalSlider"))
		{
			QSlider* slider = qobject_cast<QSlider*>(objects[ki]);
			connect(slider, &QSlider::valueChanged, this, &MainWindow::setColorValue);
		}
		else if (objects[ki]->objectName().startsWith("lineEdit"))
		{
			QLineEdit* lineEdit = qobject_cast<QLineEdit*>(objects[ki]);
			connect(lineEdit, &QLineEdit::textChanged, this, &MainWindow::setColorText);
		}
	}
	ui->horizontalSlider_lightBarAngleMin->setRange(0, 3600);
	ui->horizontalSlider_lightBarAngleMax->setRange(0, 3600);
	ui->horizontalSlider_lightBarAreaMin->setRange(0, 5000);
	ui->horizontalSlider_lightBarAreaMax->setRange(0, 5000);
	ui->horizontalSlider_lightBarPropMin->setRange(0, 3000);
	ui->horizontalSlider_lightBarPropMax->setRange(0, 3000);
	ui->horizontalSlider_lightBarAngleDiff->setRange(0, 3600);
	ui->horizontalSlider_lightBarAreaDiff->setRange(0, 6000);
	ui->horizontalSlider_lightBarlongPropMax->setRange(0, 300);
	ui->horizontalSlider_lightBarlongPropMin->setRange(0, 300);
	ui->horizontalSlider_armorAngleMin->setRange(0, 3600);
	ui->horizontalSlider_armorAreaMin->setRange(0, 60000);
	ui->horizontalSlider_armorAreaMax->setRange(0, 60000);
	ui->horizontalSlider_smallArmorPropMin->setRange(0, 600);
	ui->horizontalSlider_smallArmorPropMax->setRange(0, 600);
	ui->horizontalSlider_bigArmorPropMin->setRange(0, 600);
	ui->horizontalSlider_bigArmorPropMax->setRange(0, 600);
	ui->horizontalSlider_smallDistanceParam->setRange(0, 20000);
	ui->horizontalSlider_bigDistanceParam->setRange(0, 20000);

	ui->lineEdit_lightBarAngleMin->setValidator(new QIntValidator(0, 3600, this));
	ui->lineEdit_lightBarAngleMax->setValidator(new QIntValidator(0, 3600, this));
	ui->lineEdit_lightBarAreaMin->setValidator(new QIntValidator(0, 5000, this));
	ui->lineEdit_lightBarAreaMax->setValidator(new QIntValidator(0, 5000, this));
	ui->lineEdit_lightBarPropMin->setValidator(new QIntValidator(0, 3000, this));
	ui->lineEdit_lightBarPropMax->setValidator(new QIntValidator(0, 3000, this));
	ui->lineEdit_lightBarAngleDiff->setValidator(new QIntValidator(0, 3600, this));
	ui->lineEdit_lightBarAreaDiff->setValidator(new QIntValidator(0, 6000, this));
	ui->lineEdit_lightBarlongPropMax->setValidator(new QIntValidator(0, 300, this));
	ui->lineEdit_lightBarlongPropMin->setValidator(new QIntValidator(0, 300, this));
	ui->lineEdit_armorAngleMin->setValidator(new QIntValidator(0, 3600, this));
	ui->lineEdit_armorAreaMin->setValidator(new QIntValidator(0, 60000, this));
	ui->lineEdit_armorAreaMax->setValidator(new QIntValidator(0, 60000, this));
	ui->lineEdit_smallArmorPropMin->setValidator(new QIntValidator(0, 600, this));
	ui->lineEdit_smallArmorPropMax->setValidator(new QIntValidator(0, 600, this));
	ui->lineEdit_bigArmorPropMin->setValidator(new QIntValidator(0, 600, this));
	ui->lineEdit_bigArmorPropMax->setValidator(new QIntValidator(0, 600, this));
	ui->lineEdit_smallDistanceParam->setValidator(new QIntValidator(0, 20000, this));
	ui->lineEdit_bigDistanceParam->setValidator(new QIntValidator(0, 20000, this));
	cmdMapInit();
	initCheckBox();
}

void MainWindow::cmdMapInit()
{
	m_cmdMap.clear();
	m_cmdMap.insert("color", TCP_GET_COLOR);
	m_cmdMap.insert("hMax", TCP_GET_H_MAX);
	m_cmdMap.insert("hMin", TCP_GET_H_MIN);
	m_cmdMap.insert("sMax", TCP_GET_S_MAX);
	m_cmdMap.insert("sMin", TCP_GET_S_MIN);
	m_cmdMap.insert("vMax", TCP_GET_V_MAX);
	m_cmdMap.insert("vMin", TCP_GET_V_MIN);

	m_cmdMap.insert("lightBarAngleMin", TCP_GET_LIGHT_ANGLE_MIN);
	m_cmdMap.insert("lightBarAngleMax", TCP_GET_LIGHT_ANGLE_MAX);
	m_cmdMap.insert("lightBarAreaMin", TCP_GET_LIGHT_AREA_MIN);
	m_cmdMap.insert("lightBarAreaMax", TCP_GET_LIGHT_AREA_MAX);
	m_cmdMap.insert("lightBarPropMin", TCP_GET_LIGHT_PROP_MIN);
	m_cmdMap.insert("lightBarPropMax", TCP_GET_LIGHT_PROP_MAX);
	m_cmdMap.insert("lightBarAngleDiff", TCP_GET_LIGHT_ANGLE_DIFF);
	m_cmdMap.insert("lightBarAreaDiff", TCP_GET_LIGHT_AREA_DIFF);
	m_cmdMap.insert("lightBarlongPropMax", TCP_GET_LIGHT_LONG_PORP_AREA_DIFF_MAX);
	m_cmdMap.insert("lightBarlongPropMin", TCP_GET_LIGHT_LONG_PORP_AREA_DIFF_MIN);

	m_cmdMap.insert("armorAngleMin", TCP_GET_ARMOR_ANGLE_MIN);
	m_cmdMap.insert("armorAreaMin", TCP_GET_ARMOR_AREA_MIN);
	m_cmdMap.insert("armorAreaMax", TCP_GET_ARMOR_AREA_MAX);
	m_cmdMap.insert("smallArmorPropMin", TCP_GET_SMALL_ARMOR_PROP_MIN);
	m_cmdMap.insert("smallArmorPropMax", TCP_GET_SMALL_ARMOR_PROP_MAX);
	m_cmdMap.insert("bigArmorPropMin", TCP_GET_BIG_ARMOR_PROP_MIN);
	m_cmdMap.insert("bigArmorPropMax", TCP_GET_BIG_ARMOR_PROP_MAX);
	m_cmdMap.insert("smallDistanceParam", TCP_GET_SMALL_DISTANCE_PARAM);
	m_cmdMap.insert("bigDistanceParam", TCP_GET_BIG_DISTANCE_PARAM);

	m_cmdMap.insert("lightBarAngleMinDebug", TCP_DEBUG_LIGHT_ANGLE);
	m_cmdMap.insert("lightBarAngleMaxDebug", TCP_DEBUG_LIGHT_ANGLE);
	m_cmdMap.insert("lightBarAreaMinDebug", TCP_DEBUG_LIGHT_AREA);
	m_cmdMap.insert("lightBarAreaMaxDebug", TCP_DEBUG_LIGHT_AREA);
	m_cmdMap.insert("lightBarPropMinDebug", TCP_DEBUG_LIGHT_PROP);
	m_cmdMap.insert("lightBarPropMaxDebug", TCP_DEBUG_LIGHT_PROP);
	m_cmdMap.insert("lightBarAngleDiffDebug", TCP_DEBUG_LIGHT_ANGLE_DIFF);
	m_cmdMap.insert("lightBarAreaDiffDebug", TCP_DEBUG_LIGHT_AREA_DIFF);
	m_cmdMap.insert("lightBarlongPropMaxDebug", TCP_DEBUG_LIGHT_LONG_PROP);
	m_cmdMap.insert("lightBarlongPropMinDebug", TCP_DEBUG_LIGHT_LONG_PROP);

	m_cmdMap.insert("armorAngleMinDebug", TCP_DEBUG_ARMOR_ANGLE);
	m_cmdMap.insert("armorAreaMinDebug", TCP_DEBUG_ARMOR_AREA);
	m_cmdMap.insert("armorAreaMaxDebug", TCP_DEBUG_ARMOR_AREA);
	m_cmdMap.insert("smallArmorPropMinDebug", TCP_DEBUG_SMALL_ARMOR_PROP);
	m_cmdMap.insert("smallArmorPropMaxDebug", TCP_DEBUG_SMALL_ARMOR_PROP);
	m_cmdMap.insert("bigArmorPropMinDebug", TCP_DEBUG_BIG_ARMOR_PROP);
	m_cmdMap.insert("bigArmorPropMaxDebug", TCP_DEBUG_BIG_ARMOR_PROP);
	m_cmdMap.insert("smallDistanceParamDebug", TCP_DEBUG_SMALL_ARMOR_DISTANCE);
	m_cmdMap.insert("bigDistanceParamDebug", TCP_DEBUG_BIG_ARMOR_DISTANCE);

}

void MainWindow::setColorValue(int value)
{
	imageMutex.lock();
	mp_imageTimer->stop();
	QSlider* slider = qobject_cast<QSlider*>(sender());
	QObjectList list = slider->parent()->children();
	QString objectName = QObject::sender()->objectName().split("_").last();
	for (size_t ki = 0; ki < list.size(); ki++)
	{
		if (list[ki]->objectName().contains(objectName) && list[ki]->objectName().startsWith("lineEdit"))
		{
			qobject_cast<QLineEdit*>(list[ki])->setText(QString::number(value));
		}
	}
	S_SendProtocol sendData = {};
	sendData.HeadStart	= 0xaa;
	sendData.HeadEnd = 0xbb;
	sendData.Cmd = m_cmdMap[objectName] - 1;
	memcpy(sendData.value, &value, sizeof(value));
	sendData.Length = sizeof(sendData);
	m_socket.SendData(sendData);
	mp_imageTimer->start();
	imageMutex.unlock();
}

void MainWindow::setColorText(QString value)
{
	QLineEdit* lineEdit = qobject_cast<QLineEdit*>(sender());
	QObjectList list = lineEdit->parent()->children();
	QString objectName = QObject::sender()->objectName().split("_").last();
	for (size_t ki = 0; ki < list.size(); ki++)
	{
		if (list[ki]->objectName().contains(objectName) && list[ki]->objectName().startsWith("horizontalSlider"))
		{
			qobject_cast<QSlider*>(list[ki])->setValue(value.toInt());
		}
	}
}

void MainWindow::changeSliderValue(uint8_t cmd, int value)
{
	QString name;
	QObjectList objects;
	objects.append(ui->tabWidgetPageColor->children());
	objects.append(ui->tabWidgetPageShape->children());
	objects.append(ui->tabWidgetPageArmor->children());

	QMap<QString, uint8_t>::iterator it; //遍历map  
	for (it = m_cmdMap.begin(); it != m_cmdMap.end(); ++it)
	{
		if (it.value() == cmd)
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

/*************以下是Checkbox**************/

void MainWindow::initCheckBox()
{
	QObjectList objects;
	objects.append(ui->tabWidgetPageColor->children());
	objects.append(ui->tabWidgetPageShape->children());
	objects.append(ui->tabWidgetPageArmor->children());
	
	for (size_t ki = 0; ki < objects.size(); ki++)
	{
		if (objects[ki]->objectName().startsWith("checkBox"))
		{
			QCheckBox* checkBox = qobject_cast<QCheckBox*>(objects[ki]);
			connect(checkBox, &QCheckBox::stateChanged, this, &MainWindow::setDebugOutput);
		}
	}
}

void MainWindow::setDebugOutput(int value)
{
	QCheckBox* checkBox = qobject_cast<QCheckBox*>(sender());
	QString objectName = checkBox->objectName().split("_").last() + "Debug";
	S_SendProtocol sendData = {};
	sendData.HeadStart = 0xaa;
	sendData.HeadEnd = 0xbb;
	if (!m_cmdMap.contains(objectName))
		return;
	sendData.Cmd = m_cmdMap[objectName];
	memcpy(sendData.value, &value, sizeof(value));
	sendData.Length = sizeof(sendData);
	m_socket.SendData(sendData);
}
