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


SOURCES +=\
    network/packets/packet.cpp \
    network/packets/varint.cpp \
    network/Client.cpp \
    network/mytcpsocket.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS  += \
    network/packets/packet.h \
    network/packets/varint.h \
    network/Client.h \
    network/mytcpsocket.h \
    mainwindow.h

FORMS    += mainwindow.ui

DISTFILES += \
    network/packets/clientbound/test.txt
