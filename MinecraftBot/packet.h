/* packet.h
 * Header file for the Packet class
 * */
#ifndef PACKET_H
#define PACKET_H

#include "varint.h"
#include <string>
#include <QByteArray>
#include <QString>
#include "mytcpsocket.h"
#include <QColor>
#include "mainwindow.h"
#include <QtZlib/zlib.h>

class Packet
{
public:
    Packet();
    Packet(const QByteArray &data, bool compressed);
    //Functions
    QByteArray packPacket(const QByteArray &data, bool compress=false);
    QByteArray packString(const std::string &text);
    int sendPacket(const QByteArray &data);
    void appendVarint(QByteArray &input, int value);
    QByteArray uncompress(QByteArray compressed);

    //Vars
    int packetID;
    int packetSize;
    QByteArray data;
    MyTcpSocket * socket;
    MainWindow * ui;
    QColor displayColor;

};

#endif // PACKET_H
