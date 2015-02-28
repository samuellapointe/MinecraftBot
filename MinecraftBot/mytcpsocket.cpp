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
void MyTcpSocket::doConnect(const QString &ip, const int port)
{
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
}

void MyTcpSocket::bytesWritten(qint64 bytes)
{
    //ui->writeToConsole(QString::number(bytes) + " bytes written...");
}

void MyTcpSocket::readyRead()
{
    //ui->writeToConsole("reading...");

    // read the data from the socket
    QByteArray received = socket->readAll();    //ui->writeToConsole(received);
    //Interpret it
    client->decodePacket(received);
}

void MyTcpSocket::write(QByteArray data)
{
    QByteArray encryptedData = data;
    if(client->encrypted)
    {
        encryptedData = client->crypt->encodeAES(data);
    }
    socket->write(encryptedData);
    //socket->waitForBytesWritten(5000);
}

