/* packet.h
 * Header file for the Packet class
 * */
#ifndef PACKET_H
#define PACKET_H

#include "varint.h"
#include <string>
#include <QByteArray>
#include <QString>

using namespace std;

class Packet
{
public:
    QByteArray packPacket(const QByteArray &data, bool compress=false);
    QByteArray packString(const string &text);
    void appendVarint(QByteArray &input, int value);
    int packetID;
    int packetSize;
};

#endif // PACKET_H
