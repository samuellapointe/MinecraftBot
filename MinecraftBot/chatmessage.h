#ifndef CHATMESSAGE_H
#define CHATMESSAGE_H

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include "packet.h"

class ChatMessage : public Packet
{
public:
    ChatMessage(MyTcpSocket * socket, MainWindow * ui, QByteArray &data);
    ~ChatMessage();
};

#endif // CHATMESSAGE_H
