#ifndef GRAPH_H
#define GRAPH_H

#include "node.h"
#include "world.h"

class graph
{
public:
    graph(int x, int y, int z){startingX = x; startingY = y; startingZ = z;}
    ~graph();
    Node * startingPoint;
    int startingX;
    int startingY;
    int startingZ;
};

#endif // GRAPH_H
