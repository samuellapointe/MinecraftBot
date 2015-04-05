#ifndef POSITIONF_H
#define POSITIONF_H

#include "position.h"

class Positionf : public Position
{
public:
    int fScore;
    Positionf();
    Positionf(Position p, int _fScore);

    bool operator<(const Positionf pos) const;

};

#endif // POSITIONF_H
