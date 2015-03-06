#ifndef SENDCHATMESSAGE_H
#define SENDCHATMESSAGE_H

#include "packet.h"

//This packet is different than the chat message, as it is serverbound and not encoded in json.

class SendChatMessage : public Packet
{
public:
    SendChatMessage(MyTcpSocket * socket, MainWindow * ui, QString message);
    ~SendChatMessage();
    void sendPacket(bool compressed);
private:
    QString message;
};

#endif // SENDCHATMESSAGE_H
