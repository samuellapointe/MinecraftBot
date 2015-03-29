#ifndef POSITION_H
#define POSITION_H

#include "direction.h"
#include "math.h"

class Position
{
public:
    Position();
    Position(double x, double y, double z);
    ~Position();
    double x;
    double y;
    double z;

    //Operators
    Position operator+(const Position& p);
    Position operator-(const Position& p);
    Position operator*(const Position& p);
    Position operator/(const Position& p);

    Position operator+(const Direction& d);
    Position operator-(const Direction& d);

    //Functions
    Position getFloored();

    //Directions
    /*static const Position north = Position(0, 0, -1);
    static const Position south = Position(0, 0, 1);
    static const Position east = Position(1, 0, 0);
    static const Position west = Position(-1, 0, 0);
    static const Position up = Position(0, 1, 0);
    static const Position down = Position(0, -1, 0);*/
};

#endif // POSITION_H
