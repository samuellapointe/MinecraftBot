//CPP file for the Client class, which is the class handling most of the network stuff

#include "Client.h"
#include "mainwindow.h"
#include "handshake.h"
#include "loginstart.h"
#include "keepalive.h"

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
    compressionSet = false;

    socket.ui = ui; //Give the socket the interface to write to
    socket.client = this;
    socket.doConnect(ip, port);

    if(socket.connectedBool)
    {
        Handshake hs = Handshake(47, ip.toStdString(), port, 2);
        QByteArray packetTmp = hs.packPacket();
        socket.write(packetTmp);
        ui->displayPacket(false, hs.packetID, hs.packetSize, QColor(255, 200, 200), "Handshake");
        LoginStart ls = LoginStart(username);
        socket.write(ls.packPacket());
        ui->displayPacket(false, ls.packetID, ls.packetSize, QColor(200, 255, 200), "Login Start");
    }


}

void Client::decodePacket(QByteArray &data)
{
    //The first value should be a varint with the packet's size
    int nbBytesDecoded;
    uint8_t * buffer = (uint8_t*)data.data();
    uint64_t decodedSize = Varint::decode_unsigned_varint(buffer, nbBytesDecoded);
    data = data.right(data.length() - nbBytesDecoded); //Remove the bytes decoded so far

    if(compressionSet)
    {
        //Next, the data length, 0 if uncompressed. Don't need to care about compressed packets right now so I'll only interpret those with the value 0.
        buffer = (uint8_t*)data.data();
        uint64_t uncompressedLength = Varint::decode_unsigned_varint(buffer, nbBytesDecoded);

        if(uncompressedLength == 0) //If it's not compressed
        {
            //Next, the packet ID
            data = data.right(data.length() - nbBytesDecoded); //Remove the bytes decoded so far
            buffer = (uint8_t*)data.data();
            uint64_t decodedID = Varint::decode_unsigned_varint(buffer, nbBytesDecoded);
            data = data.right(data.length() - nbBytesDecoded);
            handlePacket(decodedID, decodedSize, data);

        }
    }
    else
    {
        buffer = (uint8_t*)data.data();
        uint64_t decodedID = Varint::decode_unsigned_varint(buffer, nbBytesDecoded);
        data = data.right(data.length() - nbBytesDecoded);
        handlePacket(decodedID, decodedSize, data);
    }
}

void Client::handlePacket(int packetID, int packetSize, QByteArray &data)
{
    switch(packetID)
    {
    case 1: //Encryption request
        ui->displayPacket(true, packetID, packetSize, QColor(255, 100, 100), "Encryption request");
        break;
    case 3:
        {
            if(!compressionSet) //Set compression
            {
                compressionSet = true; //ID 3 sets compression in the login phase
                ui->displayPacket(true, packetID, packetSize, QColor(100,125,255), "Set compression!");
            }
            else //Keep alive
            {
                ui->displayPacket(true, packetID, packetSize, QColor(150,150,255), "Keep alive");
                KeepAlive ka = KeepAlive(data);
                socket.write(ka.packPacket());
                ui->displayPacket(false, ka.packetID, ka.packetSize, QColor(150, 200, 200), "Keep alive");
            }
        }
        break;
    default:
        if(ui->showUnknownPackets())
        {
            ui->displayPacket(true, packetID, packetSize);
        }
        break;
    }

}
