/********************************************************************************
** Form generated from reading UI file 'mainwindowg16896.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef MAINWINDOWG16896_H
#define MAINWINDOWG16896_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionSSH;
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout_6;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_4;
    QLabel *Image_frame;
    QLabel *Image_binary;
    QHBoxLayout *horizontalLayout_5;
    QLabel *Image_finall;
    QLabel *Image_backup;
    QTabWidget *tabWidget;
    QWidget *tabWidgetPage1;
    QVBoxLayout *verticalLayout_4;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_3;
    QSlider *horizontalSlider_color;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_4;
    QSlider *horizontalSlider_hMax;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label_5;
    QSlider *horizontalSlider_hMin;
    QSpacerItem *verticalSpacer_3;
    QHBoxLayout *horizontalLayout_10;
    QLabel *label_6;
    QSlider *horizontalSlider_sMax;
    QSpacerItem *verticalSpacer_4;
    QHBoxLayout *horizontalLayout_11;
    QLabel *label_7;
    QSlider *horizontalSlider_sMin;
    QSpacerItem *verticalSpacer_5;
    QHBoxLayout *horizontalLayout_12;
    QLabel *label_8;
    QSlider *horizontalSlider_vMax;
    QSpacerItem *verticalSpacer_6;
    QHBoxLayout *horizontalLayout_13;
    QLabel *label_9;
    QSlider *horizontalSlider_vMin;
    QWidget *tab;
    QGroupBox *groupBox_3;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *lineEdit_ip;
    QLabel *label_2;
    QLineEdit *lineEdit_port;
    QPushButton *pushButton;
    QMenuBar *menubar;
    QMenu *menu;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1082, 634);
        actionSSH = new QAction(MainWindow);
        actionSSH->setObjectName(QStringLiteral("actionSSH"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        horizontalLayout_3 = new QHBoxLayout(centralwidget);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetMinimumSize);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy);
        groupBox->setLayoutDirection(Qt::LeftToRight);
        horizontalLayout_6 = new QHBoxLayout(groupBox);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        Image_frame = new QLabel(groupBox);
        Image_frame->setObjectName(QStringLiteral("Image_frame"));
        Image_frame->setStyleSheet(QStringLiteral("background-color: rgb(152, 152, 152);"));

        horizontalLayout_4->addWidget(Image_frame);

        Image_binary = new QLabel(groupBox);
        Image_binary->setObjectName(QStringLiteral("Image_binary"));
        Image_binary->setStyleSheet(QStringLiteral("background-color: rgb(152, 152, 152);"));

        horizontalLayout_4->addWidget(Image_binary);


        verticalLayout_2->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        Image_finall = new QLabel(groupBox);
        Image_finall->setObjectName(QStringLiteral("Image_finall"));
        Image_finall->setStyleSheet(QStringLiteral("background-color: rgb(152, 152, 152);"));

        horizontalLayout_5->addWidget(Image_finall);

        Image_backup = new QLabel(groupBox);
        Image_backup->setObjectName(QStringLiteral("Image_backup"));
        Image_backup->setStyleSheet(QStringLiteral("background-color: rgb(152, 152, 152);"));

        horizontalLayout_5->addWidget(Image_backup);


        verticalLayout_2->addLayout(horizontalLayout_5);


        horizontalLayout_6->addLayout(verticalLayout_2);


        horizontalLayout_2->addWidget(groupBox);

        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        sizePolicy.setHeightForWidth(tabWidget->sizePolicy().hasHeightForWidth());
        tabWidget->setSizePolicy(sizePolicy);
        tabWidget->setMinimumSize(QSize(300, 0));
        tabWidget->setMaximumSize(QSize(300, 16777215));
        tabWidgetPage1 = new QWidget();
        tabWidgetPage1->setObjectName(QStringLiteral("tabWidgetPage1"));
        verticalLayout_4 = new QVBoxLayout(tabWidgetPage1);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        label_3 = new QLabel(tabWidgetPage1);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout_7->addWidget(label_3);

        horizontalSlider_color = new QSlider(tabWidgetPage1);
        horizontalSlider_color->setObjectName(QStringLiteral("horizontalSlider_color"));
        horizontalSlider_color->setOrientation(Qt::Horizontal);

        horizontalLayout_7->addWidget(horizontalSlider_color);


        verticalLayout_3->addLayout(horizontalLayout_7);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        label_4 = new QLabel(tabWidgetPage1);
        label_4->setObjectName(QStringLiteral("label_4"));

        horizontalLayout_8->addWidget(label_4);

        horizontalSlider_hMax = new QSlider(tabWidgetPage1);
        horizontalSlider_hMax->setObjectName(QStringLiteral("horizontalSlider_hMax"));
        horizontalSlider_hMax->setOrientation(Qt::Horizontal);

        horizontalLayout_8->addWidget(horizontalSlider_hMax);


        verticalLayout_3->addLayout(horizontalLayout_8);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_2);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        label_5 = new QLabel(tabWidgetPage1);
        label_5->setObjectName(QStringLiteral("label_5"));

        horizontalLayout_9->addWidget(label_5);

        horizontalSlider_hMin = new QSlider(tabWidgetPage1);
        horizontalSlider_hMin->setObjectName(QStringLiteral("horizontalSlider_hMin"));
        horizontalSlider_hMin->setOrientation(Qt::Horizontal);

        horizontalLayout_9->addWidget(horizontalSlider_hMin);


        verticalLayout_3->addLayout(horizontalLayout_9);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_3);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName(QStringLiteral("horizontalLayout_10"));
        label_6 = new QLabel(tabWidgetPage1);
        label_6->setObjectName(QStringLiteral("label_6"));

        horizontalLayout_10->addWidget(label_6);

        horizontalSlider_sMax = new QSlider(tabWidgetPage1);
        horizontalSlider_sMax->setObjectName(QStringLiteral("horizontalSlider_sMax"));
        horizontalSlider_sMax->setOrientation(Qt::Horizontal);

        horizontalLayout_10->addWidget(horizontalSlider_sMax);


        verticalLayout_3->addLayout(horizontalLayout_10);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_4);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setObjectName(QStringLiteral("horizontalLayout_11"));
        label_7 = new QLabel(tabWidgetPage1);
        label_7->setObjectName(QStringLiteral("label_7"));

        horizontalLayout_11->addWidget(label_7);

        horizontalSlider_sMin = new QSlider(tabWidgetPage1);
        horizontalSlider_sMin->setObjectName(QStringLiteral("horizontalSlider_sMin"));
        horizontalSlider_sMin->setOrientation(Qt::Horizontal);

        horizontalLayout_11->addWidget(horizontalSlider_sMin);


        verticalLayout_3->addLayout(horizontalLayout_11);

        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_5);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setObjectName(QStringLiteral("horizontalLayout_12"));
        label_8 = new QLabel(tabWidgetPage1);
        label_8->setObjectName(QStringLiteral("label_8"));

        horizontalLayout_12->addWidget(label_8);

        horizontalSlider_vMax = new QSlider(tabWidgetPage1);
        horizontalSlider_vMax->setObjectName(QStringLiteral("horizontalSlider_vMax"));
        horizontalSlider_vMax->setOrientation(Qt::Horizontal);

        horizontalLayout_12->addWidget(horizontalSlider_vMax);


        verticalLayout_3->addLayout(horizontalLayout_12);

        verticalSpacer_6 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_6);

        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setObjectName(QStringLiteral("horizontalLayout_13"));
        label_9 = new QLabel(tabWidgetPage1);
        label_9->setObjectName(QStringLiteral("label_9"));

        horizontalLayout_13->addWidget(label_9);

        horizontalSlider_vMin = new QSlider(tabWidgetPage1);
        horizontalSlider_vMin->setObjectName(QStringLiteral("horizontalSlider_vMin"));
        horizontalSlider_vMin->setOrientation(Qt::Horizontal);

        horizontalLayout_13->addWidget(horizontalSlider_vMin);


        verticalLayout_3->addLayout(horizontalLayout_13);


        verticalLayout_4->addLayout(verticalLayout_3);

        tabWidget->addTab(tabWidgetPage1, QString());
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        tabWidget->addTab(tab, QString());

        horizontalLayout_2->addWidget(tabWidget);


        verticalLayout->addLayout(horizontalLayout_2);

        groupBox_3 = new QGroupBox(centralwidget);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        sizePolicy.setHeightForWidth(groupBox_3->sizePolicy().hasHeightForWidth());
        groupBox_3->setSizePolicy(sizePolicy);
        groupBox_3->setMinimumSize(QSize(0, 100));
        groupBox_3->setMaximumSize(QSize(16777215, 100));
        layoutWidget = new QWidget(groupBox_3);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(20, 20, 403, 27));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setMinimumSize(QSize(15, 25));
        label->setMaximumSize(QSize(15, 25));

        horizontalLayout->addWidget(label);

        lineEdit_ip = new QLineEdit(layoutWidget);
        lineEdit_ip->setObjectName(QStringLiteral("lineEdit_ip"));
        lineEdit_ip->setMinimumSize(QSize(130, 20));
        lineEdit_ip->setMaximumSize(QSize(130, 20));

        horizontalLayout->addWidget(lineEdit_ip);

        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setMinimumSize(QSize(25, 25));
        label_2->setMaximumSize(QSize(25, 25));

        horizontalLayout->addWidget(label_2);

        lineEdit_port = new QLineEdit(layoutWidget);
        lineEdit_port->setObjectName(QStringLiteral("lineEdit_port"));
        lineEdit_port->setMinimumSize(QSize(130, 20));
        lineEdit_port->setMaximumSize(QSize(130, 20));

        horizontalLayout->addWidget(lineEdit_port);

        pushButton = new QPushButton(layoutWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setMinimumSize(QSize(75, 25));
        pushButton->setMaximumSize(QSize(75, 25));

        horizontalLayout->addWidget(pushButton);


        verticalLayout->addWidget(groupBox_3);


        horizontalLayout_3->addLayout(verticalLayout);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 1082, 23));
        menu = new QMenu(menubar);
        menu->setObjectName(QStringLiteral("menu"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menu->menuAction());
        menu->addAction(actionSSH);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        actionSSH->setText(QApplication::translate("MainWindow", "SSH", Q_NULLPTR));
        groupBox->setTitle(QString());
        Image_frame->setText(QString());
        Image_binary->setText(QString());
        Image_finall->setText(QString());
        Image_backup->setText(QString());
        label_3->setText(QApplication::translate("MainWindow", "\347\272\242/\350\223\235", Q_NULLPTR));
        label_4->setText(QApplication::translate("MainWindow", "H_Max", Q_NULLPTR));
        label_5->setText(QApplication::translate("MainWindow", "H_Min", Q_NULLPTR));
        label_6->setText(QApplication::translate("MainWindow", "S_Max", Q_NULLPTR));
        label_7->setText(QApplication::translate("MainWindow", "S_Min", Q_NULLPTR));
        label_8->setText(QApplication::translate("MainWindow", "V_Max", Q_NULLPTR));
        label_9->setText(QApplication::translate("MainWindow", "V_Min", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tabWidgetPage1), QApplication::translate("MainWindow", "\351\242\234\350\211\262", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("MainWindow", "\345\275\242\347\212\266", Q_NULLPTR));
        groupBox_3->setTitle(QString());
        label->setText(QApplication::translate("MainWindow", "IP", Q_NULLPTR));
        label_2->setText(QApplication::translate("MainWindow", "Port", Q_NULLPTR));
        pushButton->setText(QApplication::translate("MainWindow", "\350\277\236\346\216\245", Q_NULLPTR));
        menu->setTitle(QApplication::translate("MainWindow", "\350\260\203\350\257\225", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // MAINWINDOWG16896_H
