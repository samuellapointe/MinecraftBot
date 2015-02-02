//CPP file for the Client class, which is the class handling most of the network stuff

#include "Client.h"
#include "mainwindow.h"
#include "handshake.h"
#include "loginstart.h"

Client::Client(MainWindow * i_ui, const string &i_username, const string &i_password, const QString &i_ip, const int i_port)
{
    username = i_username;
    password = i_password;
    ip = i_ip;
    port = i_port;
    ui = i_ui;

}

Client::~Client()
{
}

void Client::startConnect()
{
    socket.ui = ui; //Give the socket the interface to write to
    socket.client = this;
    socket.doConnect(ip, port);

    if(socket.connectedBool)
    {
        Handshake hs = Handshake(47, ip.toStdString(), port, 2);
        QByteArray packetTmp = hs.packPacket();
        socket.write(packetTmp);
        LoginStart ls = LoginStart(username);
        socket.write(ls.packPacket());
    }
}

void Client::decodePacket(QByteArray data)
{
    //The first value should be a varint with the packet's size
    int nbBytesDecoded;
    uint8_t * buffer = (uint8_t*)data.data();
    uint64_t decodedSize = Varint::decode_unsigned_varint(buffer, nbBytesDecoded);

    //Next, the packet ID
    //ui->writeToChat(QString::number(data.size()) + " - " + QString::number(nbBytesDecoded));
    data = data.right(data.length() - nbBytesDecoded); //Remove the bytes decoded so far
    buffer = (uint8_t*)data.data();
    uint64_t decodedID = Varint::decode_unsigned_varint(buffer, nbBytesDecoded);

    if(decodedID == 3)
    {
        ui->writeToChat("KEEP ALIVE");
        data = data.right(data.length() - nbBytesDecoded); //Remove the bytes decoded so far
        buffer = (uint8_t*)data.data();
        uint64_t decodedKeepAlive = Varint::decode_unsigned_varint(buffer, nbBytesDecoded);
        ui->writeToChat(QString::number(decodedKeepAlive));
        QByteArray tmp;
        Packet::appendVarint(tmp, decodedKeepAlive);
        socket.write(Packet::packPacket(tmp, 0));
    }

    ui->writeToChat(QString::number(decodedID));
    //ui->writeToChat(QString::number(data.size()));
    //ui->writeToChat("Nb Decoded: " + QString::number(nbBytesDecoded) + " - " + QString::number(decodedValue) + " - " + QString::number(data.size()));
}
