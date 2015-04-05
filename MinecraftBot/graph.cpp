#include "graph.h"

Graph::Graph()
{

}

Graph::~Graph()
{

}

std::list<Position> Graph::findPath(World * world, Position startPosition, Position endPosition)
{
    //Taken from http://www.briangrinstead.com/blog/astar-search-algorithm-in-javascript/

    std::map<Positionf, Node*> openList;

    Node * start = new Node(startPosition);
    start->hScore = start->coords.distance(endPosition);

    openList.emplace(std::make_pair(Positionf(start->coords, start->fScore()), start));
    //openArray[(int)tmp.x][(int)tmp.y][(int)tmp.z] = start;

    int cpt = 0;

    while(!openList.empty())
    {
        cpt++;
        Node * currentNode = openList.begin()->second;
        openList.erase(openList.begin());

        if(currentNode->coords == endPosition)
        {
            //Path found!
            std::list<Position> path;
            while(currentNode->parent != 0)
            {
                path.push_back(currentNode->coords);
                currentNode = currentNode->parent;
            }
            return path;
        }


        currentNode->closed = true;

        //Check neighbors
        for(int i = 0; i < 6; i++)
        {
            if(world->canGo(currentNode->coords, (Direction)i))
            {
                if(currentNode->neighbors[i] == 0)
                {
                    Positionf ptmp = Positionf((currentNode->coords + (Direction)i),0);
                    std::map<Positionf, Node*>::iterator iter = openList.find(ptmp);
                    if(iter != openList.end())
                    {
                        currentNode->neighbors[i] = iter->second;
                    }
                    else
                    {
                        Node * tmp = new Node(currentNode->coords + (Direction)i);
                        currentNode->neighbors[i] = tmp;
                        tmp->gScore = currentNode->gScore + 1;
                        tmp->hScore = tmp->coords.distance(endPosition);
                        openList.emplace(std::make_pair(Positionf(currentNode->coords + (Direction)i, tmp->fScore()),tmp));
                    }
                }
                Node * neighbor = currentNode->neighbors[i];

                if(!neighbor->closed)
                {
                    int gScore = currentNode->gScore + 1;
                    bool beenVisited = neighbor->visited;

                    if(!neighbor->visited || gScore < neighbor->gScore)
                    {
                        neighbor->visited = true;
                        neighbor->parent = currentNode;

                        if(!beenVisited)
                        {
                            openList.emplace(std::make_pair(Positionf(neighbor->coords, neighbor->fScore()),neighbor));
                        }
                    }

                }
            }
        }
    }
    return std::list<Position>(); //No path found
}

