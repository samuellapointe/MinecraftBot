#include "action.h"
#include "packet.h"

Action::Action()
{
    priority = 0;
}

Action::~Action()
{

}

bool Action::operator <(Action other) const
{
    return (priority < other.priority);
}

void Action::run()
{

}
