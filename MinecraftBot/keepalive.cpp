#include "keepalive.h"

KeepAlive::KeepAlive(MyTcpSocket * s, MainWindow * i_ui, QByteArray &d)
{
    data = d;
    packetID = 0;
    socket = s;
    ui = i_ui;
    displayColor = QColor(0, 200 ,0);
}

KeepAlive::~KeepAlive()
{

}

void KeepAlive::sendPacket(bool compressed)
{
    //The data buffer
    QByteArray tmp;

    //The content of the keep alive
    uint8_t * buffer = (uint8_t*)data.data();
    int nbBytesDecoded;
    uint64_t decodedKeepAlive = Varint::decode_unsigned_varint(buffer, nbBytesDecoded);

    //Append the varint decoded
    Packet::appendVarint(tmp, decodedKeepAlive);

    //Cut off the extra bytes (int64)
    tmp = tmp.left(nbBytesDecoded);

    //Call parent
    int length = Packet::sendPacket(Packet::packPacket(tmp, compressed));
    ui->displayPacket(false, packetID, length, displayColor, "Keep Alive");

}


