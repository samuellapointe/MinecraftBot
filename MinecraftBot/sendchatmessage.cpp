//This packet is different than the chat message, as it is serverbound and not encoded in json.

#include "sendchatmessage.h"

SendChatMessage::SendChatMessage(MyTcpSocket * s, MainWindow * i_ui, QString m)
{
    message = m;
    packetID = 1;
    socket = s;
    ui = i_ui;
    displayColor = QColor(0, 0, 150);
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
    int length = Packet::sendPacket(Packet::packPacket(tmp, compressed));
    ui->displayPacket(false, packetID, length, displayColor, "Chat Message");

}


