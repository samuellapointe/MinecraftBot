#include "node.h"

Node::Node()
{
    gScore = 0;
    hScore = 0;
}

Node::Node(Position _coords)
{
    coords = _coords;
    gScore = 0;
    hScore = 0;
    closed = false;
    visited = false;
    parent = 0;
    for(int i = 0; i < 6; i++)
    {
        neighbors[i] = 0;
    }
}

Node::~Node()
{

}
