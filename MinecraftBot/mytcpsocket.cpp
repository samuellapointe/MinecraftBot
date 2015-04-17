/* mytcpsocket.cpp
 * This class is used to define the socket and its operations
 * Taken from http://www.bogotobogo.com/Qt/Qt5_QTcpSocket_Signals_Slots.php
 * */

#include "mytcpsocket.h"
#include "mainwindow.h"

MyTcpSocket::MyTcpSocket(QObject *parent) :
    QObject(parent)
{
}

//Called doConnect because Qt already uses a connect function everywhere
void MyTcpSocket::doConnect(const QString &i_ip, const int i_port)
{
    ip = i_ip;
    port = i_port;

    connectedBool = false;

    //The socket iself
    socket = new QTcpSocket(this);

    //Functions to be called on events
    connect(socket, SIGNAL(connected()),this, SLOT(connected()));
    connect(socket, SIGNAL(disconnected()),this, SLOT(disconnected()));
    connect(socket, SIGNAL(bytesWritten(qint64)),this, SLOT(bytesWritten(qint64)));
    connect(socket, SIGNAL(readyRead()),this, SLOT(readyRead()));

    //Debug
    ui->writeToConsole("Connecting to "+ip+" on port "+ QString::number(port) + "...");

    //connecting
    socket->connectToHost(ip, port);

    //in case it goes wrong
    if(!socket->waitForConnected(5000))
    {
        ui->writeToConsole("Error: " + socket->errorString());
    }
}

void MyTcpSocket::connected()
{
    ui->writeToConsole("connected...");
    connectedBool=true;

}

void MyTcpSocket::disconnected()
{
    ui->writeToConsole("Disconnected!");
    connectedBool=false;
    if(ui->autoReconnect())
    {
        ui->connectClient();
    }
}

void MyTcpSocket::bytesWritten(qint64 bytes)
{
    //ui->writeToConsole(QString::number(bytes) + " bytes written...");
}

void MyTcpSocket::readyRead()
{
    int nbDecodedBytes, packetLength, bufferLength;
    // read the data from the socket
    QByteArray data = socket->readAll();    //ui->writeToConsole(received);

    //ui->writeToConsole("Downloaded");

    if(client->encrypted)//Decrypt
    {
        data = QByteArray::fromStdString(client->crypt->decodeAES(data));
    }

    bufferStream.append(data);


    while(bufferStream.size() > 0 && totalLength <= bufferStream.size())
    {
        packetLength = Varint::decodeVarint(bufferStream.left(10), nbDecodedBytes);
        totalLength = packetLength + nbDecodedBytes;
        bufferLength = bufferStream.size();

        if(totalLength <= bufferStream.size())
        {
            if(totalLength <= 0)
            {
                bufferLength = bufferStream.size();
                packetLength = Varint::decodeVarint(bufferStream, nbDecodedBytes);
                bufferStream.clear();
                ui->writeToConsole("Buffer cleared");
            }
            else
            {
                //ui->writeToConsole("Buffer size: " + QString::number(bufferStream.length()) + " Decoded size: " + QString::number(totalLength));
                client->decodePacket(bufferStream.left(totalLength));
                bufferStream = bufferStream.right(bufferStream.length() - totalLength);
            }
            totalLength = 0;
        }
    }
}

void MyTcpSocket::write(QByteArray data)
{
    QByteArray encryptedData = data;
    if(client->encrypted)
    {
        encryptedData = client->crypt->encodeAES(data);
    }
    socket->write(encryptedData);
    socket->waitForBytesWritten(30000);
}


