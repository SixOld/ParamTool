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
    LIBS += -L$$PWD/OpenSource/opencv/lib \
            -lopencv_calib3d3414d \
            -lopencv_core3414d \
            -lopencv_dnn3414d \
            -lopencv_features2d3414d \
            -lopencv_flann3414d \
            -lopencv_highgui3414d \
            -lopencv_imgcodecs3414d \
            -lopencv_imgproc3414d \
            -lopencv_ml3414d \
            -lopencv_objdetect3414d \
            -lopencv_photo3414d \
            -lopencv_shape3414d \
            -lopencv_stitching3414d \
            -lopencv_superres3414d \
            -lopencv_video3414d \
            -lopencv_videoio3414d \
            -lopencv_videostab3414d

} else {
    BUILD_TYPE = release
    LIBS += -L$$PWD/OpenSource/QSsh/lib -lQSsh
    LIBS += -L$$PWD/OpenSource/opencv/lib \
            -lopencv_calib3d3414 \
            -lopencv_core3414 \
            -lopencv_dnn3414 \
            -lopencv_features2d3414 \
            -lopencv_flann3414 \
            -lopencv_highgui3414 \
            -lopencv_imgcodecs3414 \
            -lopencv_imgproc3414 \
            -lopencv_ml3414 \
            -lopencv_objdetect3414 \
            -lopencv_photo3414 \
            -lopencv_shape3414 \
            -lopencv_stitching3414 \
            -lopencv_superres3414 \
            -lopencv_video3414 \
            -lopencv_videoio3414 \
            -lopencv_videostab3414
}

DESTDIR     = $$OUT_PWD/$$BUILD_TYPE/out
OBJECTS_DIR = $$OUT_PWD/$$BUILD_TYPE/obj
MOC_DIR     = $$OUT_PWD/$$BUILD_TYPE/moc
RCC_DIR     = $$OUT_PWD/$$BUILD_TYPE/rcc
UI_DIR      = $$OUT_PWD/$$BUILD_TYPE/ui
