#include "movementthread.h"
#include "player.h"
#include "playerposition.h"
#include <ctime>

MovementThread::MovementThread(double sp, double dis, Direction dir, MyTcpSocket * so, Player * p)
{
    speed = sp;
    distance = dis;
    direction = dir;
    socket = so;
    player = p;
    maxSpeed = 4.3; //4.3 meters per second max
    run();
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
        switch(direction)
        {
        case NORTH:
            player->position_z-=speed;
            break;
        case SOUTH:
            player->position_z+=speed;
            break;
        case EAST:
            player->position_x+=speed;
            break;
        case WEST:
            player->position_x-=speed;
            break;
        case NORTHEAST:
            player->position_z-=speed;
            player->position_x+=speed;
            break;
        case NORTHWEST:
            player->position_z-=speed;
            player->position_x-=speed;
            break;
        case SOUTHEAST:
            player->position_z+=speed;
            player->position_x+=speed;
            break;
        case SOUTHWEST:
            player->position_z+=speed;
            player->position_x-=speed;
            break;
        case UP:
            player->position_y+=speed;
            break;
        case DOWN:
            player->position_y-=speed;
            break;
        }
        //Update the position to the server
        PlayerPosition pp = PlayerPosition(socket, player->position_x, player->position_y, player->position_z, player->onGround);
        pp.sendPacket(player->client->compressionSet);
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
