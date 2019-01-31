#-------------------------------------------------
#
# Project created by QtCreator 2018-10-26T21:46:57
#
#-------------------------------------------------

QT       += core gui widgets \
            winextras \
            network \
            multimedia \
            webview \
            webengine \
            webenginewidgets \
            multimediawidgets \

TARGET = Handraw
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += exit.cpp \
           gameview.cpp \
           handraw.cpp \
           login.cpp \
           main.cpp \
           mainwindow.cpp \
           today.cpp \
           KinectController.cpp \
    networkcontrol.cpp \
    loadkinect.cpp \
    webcam.cpp \

HEADERS += exit.h \
           gameview.h \
           handraw.h \
           login.h \
           mainwindow.h \
           today.h \
           KinectController.h \
  networkcontrol.h \
    loadkinect.h \
    webcam.h \

INCLUDEPATH += "C:\Program Files\OpenNI2\Include"
LIBS += "C:\Program Files\OpenNI2\Lib\OpenNI2.lib"
INCLUDEPATH += "C:\Program Files\PrimeSense\NiTE2\Include"
LIBS += "C:\Program Files\PrimeSense\NiTE2\Lib\NiTE2.lib"

INCLUDEPATH += $$PWD/../../../Libraries/opencv3/opencv/build/include
DEPENDPATH += $$PWD/../../../Libraries/opencv3/opencv/build/include
LIBS += -L$$PWD/../../../Libraries/opencv3/opencv/build/x64/vc15/lib/ -lopencv_world344

INCLUDEPATH += $$PWD/../../../Libraries/Material/components
DEPENDPATH += $$PWD/../../../Libraries/Material/components

LIBS += -L$$PWD/../../../Libraries/Material/components/release/ -lcomponents
# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
