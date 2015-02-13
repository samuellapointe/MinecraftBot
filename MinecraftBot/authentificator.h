#ifndef AUTHENTIFICATOR_H
#define AUTHENTIFICATOR_H

#include "mainwindow.h"
#include <QObject>
#include <QNetworkAccessManager>
#include <QUrl>
#include <QNetworkRequest>
#include <QEventLoop>
#include <QNetworkReply>

class Authentificator : public QObject
{
    Q_OBJECT
public:
    explicit Authentificator(QObject *parent = 0);
    ~Authentificator();
    void authentificate(std::string username, std::string password, QByteArray hash);
    MainWindow * ui; //For writing in the console
    QByteArray getJsonParameter(QByteArray response, QByteArray parameter);
private:
    bool sendRequest(QString urlInput, QByteArray data, QByteArray & response);
signals:

public slots:

private slots:

};

#endif // AUTHENTIFICATOR_H
