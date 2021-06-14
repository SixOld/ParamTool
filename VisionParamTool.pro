QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

SOURCES += \
    ParamSave.cpp \
    SshPasswdIn.cpp \
    main.cpp \
    mainwindow.cpp \
    sshtodevice.cpp \
    SliderControl.cpp \
    SocketOperation.cpp \
	

INCLUDEPATH += $$PWD/OpenSource/QSsh/include \
                $$PWD/OpenSource/opencv/include \
                $$PWD/OpenSource/opencv/include/opencv \
                $$PWD/OpenSource/opencv/include/opencv2

HEADERS += \
    ParamSave.h \
    SshPasswdIn.h \
    mainwindow.h \
    sshtodevice.h \
    SocketOperation.h

FORMS += \
    SshPasswdIn.ui \
    mainwindow.ui \
    sshtodevice.ui

CONFIG(debug, debug|release) {
    BUILD_TYPE = debug
    LIBS += -L$$PWD/OpenSource/QSsh/lib -lQSshd
    LIBS += -L$$PWD/OpenSource/opencv/lib -lopencv_world3414d
} else {
    BUILD_TYPE = release
    LIBS += -L$$PWD/OpenSource/QSsh/lib -lQSsh
    LIBS += -L$$PWD/OpenSource/opencv/lib -lopencv_world3414
}

DESTDIR     = $$OUT_PWD/$$BUILD_TYPE/out
OBJECTS_DIR = $$OUT_PWD/$$BUILD_TYPE/obj
MOC_DIR     = $$OUT_PWD/$$BUILD_TYPE/moc
RCC_DIR     = $$OUT_PWD/$$BUILD_TYPE/rcc
UI_DIR      = $$OUT_PWD/$$BUILD_TYPE/ui
