#include "keepalive.h"

KeepAlive::KeepAlive(MyTcpSocket * s, MainWindow * i_ui, QByteArray &d)
{
    data = d;
    packetID = 0;
    socket = s;
    ui = i_ui;
}

KeepAlive::~KeepAlive()
{

}

void KeepAlive::sendPacket(bool compressed)
{
    //The data buffer
    QByteArray tmp;

    int nbDecodedBytes;
    uint8_t * buffer = (uint8_t*)data.data();
    int value = Varint::decode_unsigned_varint(buffer, nbDecodedBytes);

    //ui->writeToConsole(QString::number(value));

    appendVarint(tmp, value);

    //Call parent
    Packet::sendPacket(Packet::packPacket(tmp, compressed));

}


