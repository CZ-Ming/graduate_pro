#-------------------------------------------------
#
# Project created by QtCreator 2021-01-02T13:40:39
#
#-------------------------------------------------

QT       += core gui
QT       += network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = untitled
TEMPLATE = app

#LIBS += H:\QtFile\5.9.1\mingw53_32\lib\libopencv_*.a
#INCLUDEPATH += H:\opencv\123\opencv\opencv\build\include
#        H:\opencv\123\opencv\opencv\build\include\opencv
#        H:\opencv\123\opencv\opencv\build\include\opencv2

INCLUDEPATH+= E:\soft\opencv\opencv\opencv-build\install\include
LIBS +=E:\soft\opencv\opencv\opencv-build\lib\libopencv_*.a
# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp

HEADERS += \
        mainwindow.h

FORMS += \
        mainwindow.ui
