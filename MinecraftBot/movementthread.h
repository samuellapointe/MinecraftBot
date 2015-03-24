#ifndef MOVEMENTTHREAD_H
#define MOVEMENTTHREAD_H

#include <QThread>
#include "mytcpsocket.h"
#include "direction.h"

class Player;
class MovementThread : public QThread
{
    Q_OBJECT
public:
    MovementThread(double speed, double distance, Direction direction, MyTcpSocket * socket, Player * player);
    ~MovementThread();
protected:
    void run();
private:
    double speed;
    double distance;
    double maxSpeed;
    Direction direction;
    MyTcpSocket * socket;
    Player * player;
};

#endif // MOVEMENTTHREAD_H
