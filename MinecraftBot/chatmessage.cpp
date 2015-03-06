#include "chatmessage.h"

ChatMessage::ChatMessage(MyTcpSocket * s, MainWindow * i_ui, QByteArray &d, CommandManager * commandManager)
{
    data = d;
    packetID = 0;
    socket = s;
    ui = i_ui;
    displayColor = QColor(100,100,255);

    ui->displayPacket(true, packetID, data.length(), displayColor, "Chat Message");

    int decodedBytes;
    uint8_t * buffer = (uint8_t*)data.data();
    int messageLength = Varint::decode_unsigned_varint(buffer, decodedBytes);

    QByteArray message = data.mid(decodedBytes, messageLength);

    QJsonDocument messageDoc = QJsonDocument::fromJson(message);
    QJsonObject messageObj = messageDoc.object();
    QString translate = messageObj.value("translate").toString();

    if(translate.compare("chat.type.text") == 0) //Regular chat message
    {
        QJsonArray messageContent = messageObj.value("with").toArray();

        QJsonObject someContainer = messageContent.at(0).toObject();
        QString username = someContainer.value("insertion").toString();
        QString text = messageContent.at(1).toString();

        ui->writeToChat(username + ": " + text);
        if(text.at(0) == '!')
        {
            commandManager->readCommand(text, username);
        }
    }
    else if(translate.compare("multiplayer.player.joined") == 0) //Player joined
    {
        QJsonArray messageContent = messageObj.value("with").toArray();
        QJsonObject someContainer = messageContent.at(0).toObject();
        QString username = someContainer.value("text").toString();

        ui->writeToChat(username + " joined");
    }
    else if(translate.compare("multiplayer.player.left") == 0) //Player joined
    {
        QJsonArray messageContent = messageObj.value("with").toArray();
        QJsonObject someContainer = messageContent.at(0).toObject();
        QString username = someContainer.value("text").toString();

        ui->writeToChat(username + " left");
    }
    else if(translate.compare("chat.type.announcement") == 0)
    //Exemple: "{"translate":"chat.type.announcement","with":["Server",{"extra":["Welcome"," ","back,"," ","Knuk"],"text":""}]}"
    {
        QJsonArray messageContent = messageObj.value("with").toArray();
        QJsonObject someContainer = messageContent.at(1).toObject();
        QJsonArray extra = someContainer.value("extra").toArray();
        QString tmp = "";
        for(int i = 0; i < extra.count(); i++)
        {
            tmp += extra.at(i).toString() + " ";
        }

        ui->writeToChat(tmp);

    }
    else
    {
        ui->writeToChat(message);
    }

}

ChatMessage::~ChatMessage()
{

}

