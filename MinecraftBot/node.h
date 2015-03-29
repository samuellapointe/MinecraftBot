#ifndef NODE_H
#define NODE_H


class Node
{
public:
    Node();
    ~Node();
    Node * neighbor_north;
    Node * neighbor_south;
    Node * neighbor_east;
    Node * neighbor_west;
};

#endif // NODE_H
