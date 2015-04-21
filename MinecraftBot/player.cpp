#include "player.h"
#include "Client.h"
#include "onground.h"
#include "playerposition.h"
#include <ctime>
#include "actionmove.h"

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

void Player::move(Direction d, int distance)
{
    if(positionSet && d != NONE)
    {
        bool threadStarted = (actions.size() != 0);
        for(int i = 0; i < distance; i++)
        {
            actions.push_back(new ActionMove(d, this, socket, 0));
        }
        if(!threadStarted)
        {
            startAction();
        }
    }
}

void Player::movePath(std::vector<Direction> d)
{
    bool threadStarted = (actions.size() != 0);
    for(int i = 0; i < d.size(); i++)
    {
        actions.push_back(new ActionMove(d[i], this, socket, 100-i));
    }
    if(!threadStarted)
    {
        startAction();
    }
}

void Player::startAction()
{
    if(actions.size() > 0)
    {
        //std::make_heap(actions.begin(), actions.end()); //Order actions by priority

        QThread * thread = new QThread();
        Action * myAction = *actions.begin();
        myAction->moveToThread(thread);

        connect(thread, SIGNAL(started()), myAction, SLOT(run()));
        connect(myAction, SIGNAL(sendPacket(QByteArray)), this, SLOT(sendPacket(QByteArray)), Qt::DirectConnection);
        connect(myAction, SIGNAL(actionFinished()), this, SLOT(actionFinished()));
        connect(myAction, SIGNAL(actionFinished()), myAction, SLOT(deleteLater()));
        connect(thread, SIGNAL(actionFinished()), thread, SLOT(deleteLater()));

        thread->start();
    }
}

void Player::actionFinished()
{
    actions.erase(actions.begin());
    startAction();
}

void Player::updateGround(MyTcpSocket * socket)
{
    OnGround og = OnGround(socket, onGround);
}

void Player::sendPacket(QByteArray packet)
{
    Packet tmp;
    tmp.socket = socket;
    tmp.sendPacket(packet);
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
