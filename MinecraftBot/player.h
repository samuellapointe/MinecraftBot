//This class contains informations for the player such as its location, inventory, etc

#ifndef PLAYER_H
#define PLAYER_H

#include "mytcpsocket.h"
//#include "playerposition.h"

enum Direction{NORTH, SOUTH, EAST, WEST, NORTHEAST, NORTHWEST, SOUTHEAST, SOUTHWEST, UP, DOWN};
class Client;
class Player
{
public:
    Player(Client * client);
    ~Player();
    //Set position
    void setPositionAndLook(double x, double y, double z, float yaw, float pitch, char flags);
    void move(Direction d, MyTcpSocket * socket);
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
