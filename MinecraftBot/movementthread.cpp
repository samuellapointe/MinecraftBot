#include "movementthread.h"
#include "player.h"
#include <ctime>

MovementThread::MovementThread(double sp, double dis, Direction dir, MyTcpSocket * so, Player * p)
{
    speed = sp;
    distance = dis;
    direction = dir;
    socket = so;
    player = p;
    maxSpeed = 4.3; //4.3 meters per second max
}

MovementThread::~MovementThread()
{

}

void MovementThread::run()
{
    double distanceWalked = 0;
    //Speed is in meters per packet sent. I send them in increments of 0.1m per default
    //if I have a max speed of 4m/s, I can send a maximum of 40 packets per second
    //Which means I have to send every packet at an interval of 1sec/40 or 1sec/(maxspeed/speed)
    //to get that number of seconds in ticks, I multiply it by CLOCKS_PER_SEC
    while(distanceWalked < distance)
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
        case NORTHEAST:
            player->position.z-=speed;
            player->position.x+=speed;
            break;
        case NORTHWEST:
            player->position.z-=speed;
            player->position.x-=speed;
            break;
        case SOUTHEAST:
            player->position.z+=speed;
            player->position.x+=speed;
            break;
        case SOUTHWEST:
            player->position.z+=speed;
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
        emit(sendMovement());

        distanceWalked += speed;

        //Wait a bit
        std::clock_t startTime;
        startTime = std::clock();
        while((std::clock() - startTime)/(double)CLOCKS_PER_SEC < 1/(double)(maxSpeed/speed))
        {
            //Wait
        }
    }
}
