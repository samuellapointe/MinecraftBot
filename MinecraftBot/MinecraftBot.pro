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
    mytcpsocket.cpp \
    varint.cpp \
    handshake.cpp \
    packet.cpp \
    handshake.cpp \
    packet.cpp \
    loginstart.cpp

HEADERS  += mainwindow.h \
    Client.h \
    mytcpsocket.h \
    varint.h \
    handshake.h \
    packet.h \
    handshake.h \
    packet.h \
    loginstart.h

FORMS    += mainwindow.ui
