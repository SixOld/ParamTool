#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::initColorSlider(void)
{
	ui->horizontalSlider_color->setRange(0, 1);
	ui->horizontalSlider_hMax->setRange(0, 255);
	ui->horizontalSlider_hMin->setRange(0, 255);
	ui->horizontalSlider_sMax->setRange(0, 255);
	ui->horizontalSlider_sMin->setRange(0, 255);
	ui->horizontalSlider_vMax->setRange(0, 255);
	ui->horizontalSlider_vMin->setRange(0, 255);
	connect(ui->horizontalSlider_color, SIGNAL(valueChanged(int)), this, SLOT(setColorValue(int)));
	connect(ui->horizontalSlider_hMax, SIGNAL(valueChanged(int)), this, SLOT(setColorValue(int)));
	connect(ui->horizontalSlider_hMin, SIGNAL(valueChanged(int)), this, SLOT(setColorValue(int)));
	connect(ui->horizontalSlider_sMax, SIGNAL(valueChanged(int)), this, SLOT(setColorValue(int)));
	connect(ui->horizontalSlider_sMin, SIGNAL(valueChanged(int)), this, SLOT(setColorValue(int)));
	connect(ui->horizontalSlider_vMax, SIGNAL(valueChanged(int)), this, SLOT(setColorValue(int)));
	connect(ui->horizontalSlider_vMin, SIGNAL(valueChanged(int)), this, SLOT(setColorValue(int)));
}

void MainWindow::setColorValue(int)
{
	QString objectName = QObject::sender()->objectName().split("_").last();
}