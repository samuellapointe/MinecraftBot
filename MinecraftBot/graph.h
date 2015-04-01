#ifndef GRAPH_H
#define GRAPH_H

#include "node.h"
#include "world.h"
#include <list>
#include <vector>
#include <algorithm>

class CompareNode
{
public:
    bool operator()(const Node* x, const Node* y) const
    {
        return (x->gScore + x->hScore) > (y->gScore + y->hScore);
    }
};

class Graph
{
public:
    Graph();
    ~Graph();
    std::list<Position> findPath(World * world, Position startPosition, Position endPosition);
    Node * nodeExists(std::vector<Node*> list, Position p);
private:

};

#endif // GRAPH_H
