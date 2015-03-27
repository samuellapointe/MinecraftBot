#include "player.h"
#include "Client.h"
#include "onground.h"
#include "playerposition.h"

/* Directions:
 * North: z--
 * South: z++
 * East: x++
 * West: x--
 */

Player::Player(Client * c, MyTcpSocket * s)
{
    client = c;
    position_x = 0;
    position_y = 0;
    position_z = 0;
    yaw = 0;
    pitch = 0;
    onGround = true;
    positionSet = false;
    socket = s;
}

Player::~Player()
{

}

void Player::setPositionAndLook(double posx, double posy, double posz, float y, float p, char flags)
{
    if((flags & 1) != 0) //first bit set, relative x
    {
        position_x += posx;
    }
    else //Absolute
    {
        position_x = posx;
    }

    if((flags & 2) != 0) //second bit set, relative y
    {
        position_y += posy;
    }
    else //Absolute
    {
        position_y = posy;
    }

    if((flags & 4) != 0) //third bit set, relative z
    {
        position_z += posz;
    }
    else //Absolute
    {
        position_z = posz;
    }

    if((flags & 8) != 0) //fourth bit set, relative pitch
    {
        pitch += p;
    }
    else //Absolute
    {
        pitch = p;
    }

    if((flags & 16) != 0) //fifth bit set, relative yaw
    {
        yaw += y;
    }
    else //Absolute
    {
        yaw = y;
    }

    positionSet = true;

}

void Player::move(Direction d, double distance, MyTcpSocket * socket)
{
    if(positionSet)
    {
        QThread * thread = new QThread();
        MovementThread * mt = new MovementThread(0.1, distance, d, socket, this);
        mt->moveToThread(thread);
        connect(thread, SIGNAL(started()), mt, SLOT(run()));
        connect(mt, SIGNAL(finished()), thread, SLOT(quit()));
        connect(mt, SIGNAL(sendMovement()), this, SLOT(updateLocation()));
        connect(mt, SIGNAL(finished()), mt, SLOT(deleteLater()));
        connect(thread, SIGNAL(finished()), mt, SLOT(deleteLater()));
        thread->start();
    }
}

void Player::updateGround(MyTcpSocket * socket)
{
    if(client->world->getBlock(floor(position_x), position_y, floor(position_z)).getType() == 0 &&
       client->world->getBlock(ceil(position_x), position_y, floor(position_z)).getType() == 0 &&
       client->world->getBlock(floor(position_x), position_y, ceil(position_z)).getType() == 0 &&
       client->world->getBlock(ceil(position_x), position_y, ceil(position_z)).getType() == 0) //Block below player is air
    {
        onGround = false;
    }
    else
    {
        onGround = true;
    }
    OnGround og = OnGround(socket, onGround);
}

void Player::updateLocation()
{
    PlayerPosition pp = PlayerPosition(socket, position_x, position_y, position_z, onGround);
    pp.sendPacket(client->compressionSet);
}
