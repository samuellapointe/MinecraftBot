#ifndef ACTION_H
#define ACTION_H

#include <QThread>
#include <QDebug>

class Packet;
class Action : public QThread
{
    Q_OBJECT
public:
    Action();
    ~Action();
    short priority;
    bool operator<(const Action other) const;

signals:
    void sendPacket(QByteArray packet);
    void actionFinished();
public slots:
    virtual void run();
};

#endif // ACTION_H
