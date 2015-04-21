/* mytcpsocket.h
 * Header file for the mytcpsocket class
 * Taken from http://www.bogotobogo.com/Qt/Qt5_QTcpSocket_Signals_Slots.php
 * */
#ifndef MYTCPSOCKET_H
#define MYTCPSOCKET_H

#include <QObject>
#include <QTcpSocket>
#include <QAbstractSocket>
#include <queue>
#include <QMutex>

class MainWindow;
class Client;
class MyTcpSocket : public QObject
{
    Q_OBJECT
public:
    explicit MyTcpSocket(QObject *parent = 0);
    
    void doConnect(const QString &ip, const int port);
    MainWindow * ui; //For writing in the console
    Client * client; //To send the client the packets

    //vars
    bool connectedBool;
    bool compressionSet;
    QString ip;
    int port;
signals:

public slots:
    void connected();
    void disconnected();
    void bytesWritten(qint64 bytes);
    void readyRead();
    void write(const QByteArray &data);

private:
    QTcpSocket *socket;
    QByteArray bufferStream; //Where we store data until we know it's ready to be read
    int totalLength;
    QMutex mutex;

    
};

#endif // MYTCPSOCKET_H
