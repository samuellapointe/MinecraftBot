#include "node.h"

Node::Node(Position _nodeCoords, Position endCoords, Node * _parent)
{
    coords = _nodeCoords;
    hScore = coords.distance(endCoords);
    parent = _parent;
    if(parent != 0)
    {
        gScore = _parent->gScore + 1;
    }
    else
    {
        gScore = 0;
    }
    for(int i = 0; i < 6; i++)
    {
        neighbors[i] = 0;
    }
}

Node::~Node()
{

}
