QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

SOURCES += \
    ParamSave.cpp \
    SshPasswdIn.cpp \
    main.cpp \
    mainwindow.cpp \
    sshtodevice.cpp

INCLUDEPATH += $$PWD/OpenSource/QSsh/include

HEADERS += \
    ParamSave.h \
    SshPasswdIn.h \
    mainwindow.h \
    sshtodevice.h

FORMS += \
    SshPasswdIn.ui \
    mainwindow.ui \
    sshtodevice.ui

CONFIG(debug, debug|release) {
    BUILD_TYPE = debug
    LIBS += -L$$PWD/OpenSource/QSsh/lib -lQSshd
} else {
    BUILD_TYPE = release
    LIBS += -L$$PWD/OpenSource/QSsh/lib -lQSsh
}

DESTDIR     = $$OUT_PWD/$$BUILD_TYPE/out
OBJECTS_DIR = $$OUT_PWD/$$BUILD_TYPE/obj
MOC_DIR     = $$OUT_PWD/$$BUILD_TYPE/moc
RCC_DIR     = $$OUT_PWD/$$BUILD_TYPE/rcc
UI_DIR      = $$OUT_PWD/$$BUILD_TYPE/ui
