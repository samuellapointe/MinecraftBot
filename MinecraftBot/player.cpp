#include "player.h"
#include "Client.h"
#include "onground.h"

/* Directions:
 * North: z--
 * South: z++
 * East: x++
 * West: x--
 */

Player::Player(Client * c)
{
    client = c;
    position_x = 0;
    position_y = 0;
    position_z = 0;
    yaw = 0;
    pitch = 0;
    onGround = true;
    positionSet = false;
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
        MovementThread * mt = new MovementThread(0.1, distance, d, socket, this);
        mt->deleteLater(); //Delete when finished
    }
}

void Player::updateGround(MyTcpSocket * socket)
{
    OnGround og = OnGround(socket, onGround);
}
