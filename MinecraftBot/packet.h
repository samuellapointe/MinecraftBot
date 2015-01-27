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
    static QByteArray packPacket(const QByteArray &data, int packetID);
    static QByteArray packString(const string &text);
};

#endif // PACKET_H
