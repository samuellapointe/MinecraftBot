#-------------------------------------------------
#
# Project created by QtCreator 2015-01-20T12:46:40
#
#-------------------------------------------------

QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MinecraftBot
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    Client.cpp \
    mytcpsocket.cpp

HEADERS  += mainwindow.h \
    Client.h \
    mytcpsocket.h

FORMS    += mainwindow.ui
