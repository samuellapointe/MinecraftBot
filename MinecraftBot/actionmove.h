#ifndef ACTIONMOVE_H
#define ACTIONMOVE_H

#include "action.h"
#include "playerposition.h"
#include "player.h"

class ActionMove : public Action
{
    Q_OBJECT
public:
    ActionMove(Direction direction, Player * player, MyTcpSocket * socket, int priority);
    ~ActionMove();
signals:
    //void sendPacket(QByteArray packet);
public slots:
    void run();

private:
    Direction direction;
    Player * player;
    MyTcpSocket * socket;
};

#endif // MOVE_H
