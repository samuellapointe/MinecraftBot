#include "position.h"

Position::Position()
{
    x = 0;
    y = 0;
    z = 0;
}

Position::Position(double _x, double _y, double _z)
{
    x = _x;
    y = _y;
    z = _z;
}

Position::~Position()
{

}

Position Position::operator+(const Position& p)
{
    return Position(x + p.x, y + p.y, z + p.z);
}

Position Position::operator +(const Direction& d)
{
    switch(d)
    {
    case NORTH:
       return Position(x, y, z-1);
       break;
    case SOUTH:
       return Position(x, y, z+1);
       break;
    case EAST:
       return Position(x+1, y, z);
       break;
    case WEST:
       return Position(x-1, y, z);
       break;
    case UP:
       return Position(x, y+1, z);
       break;
    case DOWN:
       return Position(x, y-1, z);
       break;
    }
}

Position Position::operator-(const Position& p)
{
    return Position(x - p.x, y - p.y, z - p.z);
}

Position Position::operator -(const Direction& d)
{
    switch(d)
    {
    case NORTH:
       return Position(x, y, z+1);
       break;
    case SOUTH:
       return Position(x, y, z-1);
       break;
    case EAST:
       return Position(x-1, y, z);
       break;
    case WEST:
       return Position(x+1, y, z);
       break;
    case UP:
       return Position(x, y-1, z);
       break;
    case DOWN:
       return Position(x, y+1, z);
       break;
    }
}

Position Position::operator*(const Position& p)
{
    return Position(x * p.x, y * p.y, z * p.z);
}

Position Position::operator/(const Position& p)
{
    return Position(x / p.x, y / p.y, z / p.z);
}

Position Position::getFloored()
{
    return Position(floor(x), floor(y), floor(z));
}
