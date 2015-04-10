//This class contains informations for the player such as its location, inventory, etc

#ifndef PLAYER_H
#define PLAYER_H

#include "direction.h"
#include "graph.h"
#include "action.h"
#include "mytcpsocket.h"
#include <math.h>
#include <QTime>
#include <vector>

class Client;
class Player : public QObject
{
    Q_OBJECT
    friend class MovementThread; //Because I'd put them in the same class
public:
    Player(Client * client, MyTcpSocket * socket);
    ~Player();
    //Set position
    void setPositionAndLook(double x, double y, double z, float yaw, float pitch, char flags);
    void move(Direction d, int distance);
    void movePath(std::vector<Direction> d);
    void updateGround(MyTcpSocket * socket);
    bool canWalk(Direction d);
    void sendMessage(QString message);
    void goTo(Position position);
    void startAction();

    //Vars related to position
    Position position;
    bool onGround;
    bool positionSet;

public slots:
    //void updateLocation();
    void actionFinished();
    void sendPacket(QByteArray packet);
private:
    Client * client;
    MyTcpSocket * socket;
    //Vars related to look
    float yaw;
    float pitch;
    //Vars related to AI
    std::vector<Action*> actions;


};

#endif // PLAYER_H
