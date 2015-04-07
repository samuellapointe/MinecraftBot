#include "player.h"
#include "Client.h"
#include "onground.h"
#include "playerposition.h"
#include <ctime>

/* Directions:
 * North: z--
 * South: z++
 * East: x++
 * West: x--
 */

Player::Player(Client * c, MyTcpSocket * s)
{
    client = c;
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
        position.x += posx;
    }
    else //Absolute
    {
        position.x = posx;
    }

    if((flags & 2) != 0) //second bit set, relative y
    {
        position.y += posy;
    }
    else //Absolute
    {
        position.y = posy;
    }

    if((flags & 4) != 0) //third bit set, relative z
    {
        position.z += posz;
    }
    else //Absolute
    {
        position.z = posz;
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

void Player::move(Direction d, double distance)
{
    if(positionSet && d != NONE)
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

void Player::movePath(std::vector<Direction> d)
{
    if(positionSet && !d.empty())
    {
        QThread * thread = new QThread();
        MovementThread * mt = new MovementThread(0.1, 1, (*d.begin()), socket, this);
        mt->moveToThread(thread);
        connect(thread, SIGNAL(started()), mt, SLOT(run()));
        connect(mt, SIGNAL(finished()), thread, SLOT(quit()));
        connect(mt, SIGNAL(sendMovement()), this, SLOT(updateLocation()));
        connect(mt, SIGNAL(finished()), mt, SLOT(deleteLater()));
        connect(thread, SIGNAL(quit()), this, SLOT(removePathAction(d)));
        connect(thread, SIGNAL(finished()), mt, SLOT(deleteLater()));
        connect(mt, SIGNAL(movementFinished()), this, SLOT(removePathAction(d)));
        thread->start();
    }
}

void Player::removePathAction(std::vector<Direction> d)
{
    d.erase(d.begin());
    if(!d.empty())
    {
        movePath(d);
    }
}

void Player::updateGround(MyTcpSocket * socket)
{
    OnGround og = OnGround(socket, onGround);
}

void Player::updateLocation()
{
    PlayerPosition pp = PlayerPosition(socket, position.x, position.y, position.z, onGround);
    pp.sendPacket(client->compressionSet);
}

bool Player::canWalk(Direction d)
{
    return client->world->canGo(position, d);
}

void Player::sendMessage(QString message)
{
    client->sendMessage(message);
}

void Player::goTo(Position destination)
{
    QTime myTimer;
    myTimer.start();

    Graph graph = Graph();
    std::vector<Direction> path;
    path = graph.findPath(client->world, position.getFloored(), destination.getFloored());

    sendMessage(QString::number(myTimer.elapsed()) + "ms, steps:  " + QString::number(path.size()));
    movePath(path);
}
