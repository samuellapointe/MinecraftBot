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

void KeepAlive::sendPacket()
{
    //The data buffer
    QByteArray tmp;

    //The content of the keep alive
    uint8_t * buffer = (uint8_t*)data.data();
    int nbBytesDecoded;
    uint64_t decodedKeepAlive = Varint::decode_unsigned_varint(buffer, nbBytesDecoded);

    //Packet::appendVarint(tmp, 0); //Tell the server it's not compressed
    Packet::appendVarint(tmp, decodedKeepAlive);

    //Call parent
    int length = Packet::sendPacket(Packet::packPacket(tmp));
    ui->displayPacket(false, packetID, length, displayColor, "Keep Alive");

}


