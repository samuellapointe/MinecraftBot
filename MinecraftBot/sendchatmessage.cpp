//This packet is different than the chat message, as it is serverbound and not encoded in json.

#include "sendchatmessage.h"

SendChatMessage::SendChatMessage(MyTcpSocket * s, MainWindow * i_ui, QString m)
{
    message = m;
    packetID = 1;
    socket = s;
    ui = i_ui;
}

SendChatMessage::~SendChatMessage()
{

}

void SendChatMessage::sendPacket(bool compressed)
{
    //The data buffer
    QByteArray tmp;

    int messageLength = message.length();

    appendVarint(tmp, messageLength);
    tmp.append(message);

    //Call parent
    Packet::sendPacket(Packet::packPacket(tmp, compressed));

}


