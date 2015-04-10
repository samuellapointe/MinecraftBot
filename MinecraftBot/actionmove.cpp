#include "actionmove.h"

ActionMove::ActionMove(Direction _direction, Player * _player, MyTcpSocket * _socket, int _priority)
{
    direction = _direction;
    player = _player;
    priority = _priority;
    socket = _socket;
}

ActionMove::~ActionMove()
{

}

void ActionMove::run()
{
    float speed = 0.1;
    float maxSpeed = 4.3;
    double distanceWalked = 0;
    //Speed is in meters per packet sent. I send them in increments of 0.1m per default
    //if I have a max speed of 4m/s, I can send a maximum of 40 packets per second
    //Which means I have to send every packet at an interval of 1sec/40 or 1sec/(maxspeed/speed)
    //to get that number of seconds in ticks, I multiply it by CLOCKS_PER_SEC
    while(distanceWalked < 1)
    {
        if(!player->canWalk(direction))
        {
            //player->sendMessage("LOL");
        }
        switch(direction)
        {
        case NORTH:
            player->position.z-=speed;
            break;
        case SOUTH:
            player->position.z+=speed;
            break;
        case EAST:
            player->position.x+=speed;
            break;
        case WEST:
            player->position.x-=speed;
            break;
        case UP:
            player->position.y+=speed;
            break;
        case DOWN:
            player->position.y-=speed;
            break;
        }
        //Update the position to the server
        emit(sendPacket(PlayerPosition(socket, player->position.x, player->position.y, player->position.z, player->onGround).getPacket(socket->compressionSet)));

        distanceWalked += speed;

        //Wait a bit
        std::clock_t startTime;
        startTime = std::clock();
        while((std::clock() - startTime)/(double)CLOCKS_PER_SEC < 1/(double)(maxSpeed/speed))
        {
            //Wait
        }
    }
    emit actionFinished();
}
