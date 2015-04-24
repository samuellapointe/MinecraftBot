#ifndef NODE_H
#define NODE_H

#include "position.h"

class Node
{
public:
    Node(Position nodeCoords, Position targetCoords, Node * parent);
    ~Node();
    Node * neighbors[6];
    Node * parent; //Where we came from
    Position coords;
    int gScore; //Number of steps
    int hScore; //Heuristic score;

    int fScore(){return gScore + hScore;};

    /*bool operator<(const Node& node) const
    {
        return (gScore + hScore) < (node.gScore + node.hScore);
    }*/
};

#endif // NODE_H
