//This class contains informations for the player such as its location, inventory, etc

#ifndef PLAYER_H
#define PLAYER_H

#include "mytcpsocket.h"
#include "direction.h"
#include "movementthread.h"

class Client;
class Player
{
    friend class MovementThread; //Because I'd put them in the same class
public:
    Player(Client * client);
    ~Player();
    //Set position
    void setPositionAndLook(double x, double y, double z, float yaw, float pitch, char flags);
    void move(Direction d, double distance, MyTcpSocket * socket);
    void updateGround(MyTcpSocket * socket);
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

};

#endif // PLAYER_H
