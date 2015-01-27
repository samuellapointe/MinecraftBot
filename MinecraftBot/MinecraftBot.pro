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
    network/packets/packet.cpp \
    network/packets/varint.cpp \
    network/Client.cpp \
    network/mytcpsocket.cpp

HEADERS  += mainwindow.h \
    network/packets/packet.h \
    network/packets/varint.h \
    network/Client.h \
    network/mytcpsocket.h


FORMS    += mainwindow.ui
