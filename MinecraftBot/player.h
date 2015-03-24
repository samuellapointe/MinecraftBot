//This class contains informations for the player such as its location, inventory, etc

#ifndef PLAYER_H
#define PLAYER_H

#include "mytcpsocket.h"
#include "direction.h"
#include <QThread>
#include <QtConcurrent/QtConcurrent>
#include <ctime>
#include <QMutex>

using namespace QtConcurrent;

class Client;
class Player
{
public:
    Player(Client * client);
    ~Player();
    //Set position
    void setPositionAndLook(double x, double y, double z, float yaw, float pitch, char flags);
    void move(Direction d, double distance, MyTcpSocket * socket);
    void updateGround(MyTcpSocket * socket);
    void updateCoords(MyTcpSocket * socket);
private:
    Client * client;
    //Vars related to position
    double position_x;
    double position_y;
    double position_z;
    bool onGround;
    bool positionSet;
    //Vars related to look
    float yaw;
    float pitch;
    void moveThread(double distance, Direction direction, MyTcpSocket * socket);
    QMutex mutex;

};

#endif // PLAYER_H
