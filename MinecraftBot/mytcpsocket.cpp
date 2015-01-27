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

    //TO REPLACE
    //socket->write("HEAD / HTTP/1.0\r\n\r\n\r\n\r\n");
}

void MyTcpSocket::disconnected()
{
    ui->writeToConsole("Disconnected!");
}

void MyTcpSocket::bytesWritten(qint64 bytes)
{
    ui->writeToConsole(QString::number(bytes) + " bytes written...");
}

void MyTcpSocket::readyRead()
{
    ui->writeToConsole("reading...");

    // read the data from the socket
    ui->writeToConsole(socket->readAll());
}
