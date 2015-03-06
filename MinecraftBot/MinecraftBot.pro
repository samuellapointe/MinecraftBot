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

include(packets.pri)

SOURCES += main.cpp\
        mainwindow.cpp \
    Client.cpp \
    mytcpsocket.cpp \
    varint.cpp \
    cryptmanager.cpp \
    authentificator.cpp \
    commandmanager.cpp


HEADERS  += mainwindow.h \
    Client.h \
    mytcpsocket.h \
    varint.h \
    cryptmanager.h \
    authentificator.h \
    commandmanager.h

FORMS    += mainwindow.ui

INCLUDEPATH += $$PWD/cryptoInclude
#LIBS += -L"$$_PRO_FILE_PWD_/cryptoLib" -lcryptopp
LIBS += -L"$$_PRO_FILE_PWD_/cryptoLib" -lcryptlib
