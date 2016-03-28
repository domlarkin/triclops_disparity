#-------------------------------------------------
#
# Project created by QtCreator 2016-03-27T00:04:22
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qtTutorial01
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
    camera_system.cpp \
    mat2qimage.cpp

HEADERS  += mainwindow.h \
    camera_system.h \
    common.h \
    mat2qimage.h

FORMS    += mainwindow.ui

unix: CONFIG += link_pkgconfig
unix: PKGCONFIG += opencv

unix: LIBS    += -ltriclops -lpnmutils -lflycapture -lflycapture2bridge -lpthread -ldl -lm

INCLUDEPATH += /usr/include/triclops
INCLUDEPATH += /usr/include/flycapture
INCLUDEPATH += /usr/include/opencv
INCLUDEPATH += /usr/include/opencv2

DISTFILES +=

RESOURCES += \
    resources.qrc

