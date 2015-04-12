#include "graph.h"

Graph::Graph()
{

}

Graph::~Graph()
{

}

std::vector<Direction> Graph::findPath(World * world, Position startPosition, Position endPosition)
{
    //Taken from http://www.briangrinstead.com/blog/astar-search-algorithm-in-javascript/

    //std::map<Positionf, Node*> openList;
    std::vector<Node*> openList;

    Node * start = new Node(startPosition);
    start->hScore = start->coords.distance(endPosition);

    //openList.emplace(std::make_pair(Positionf(start->coords, start->fScore()), start));
    openList.push_back(start);

    //openArray[(int)tmp.x][(int)tmp.y][(int)tmp.z] = start;

    int cpt = 0;

    while(!openList.empty())
    {
        cpt++;
        Node * currentNode = openList.front();
        for(int i = 0; i < openList.size(); i++)
        {
            if(openList[i]->fScore() < currentNode->fScore() && !openList[i]->closed)
            {
                currentNode = openList[i];
            }
        }
        //openList.erase(openList.begin());

        if(currentNode->coords == endPosition)
        {
            //Path found!
            std::vector<Position> path;
            std::vector<Direction> directions;
            while(currentNode->parent != 0)
            {
                path.push_back(currentNode->coords);
                currentNode = currentNode->parent;
            }
            path.push_back(startPosition);
            std::reverse(path.begin(), path.end());
            for(int i = 0; i < path.size() - 1; i++)
            {
                directions.push_back(Position::getDirectionFromPosition(path[i+1]-path[i]));
            }
            return directions;
        }


        currentNode->closed = true;

        //Check neighbors
        for(int i = 0; i < 6; i++)
        {
            if(world->canGo(currentNode->coords, (Direction)i))
            {
                if(currentNode->neighbors[i] == 0)
                {
                    currentNode->neighbors[i] = findNode(openList, currentNode->coords + (Direction)i);
                    if(currentNode->neighbors[i]->gScore == 0)
                    {
                        currentNode->neighbors[i]->gScore = currentNode->gScore + 1;
                    }
                    /*Positionf ptmp = Positionf((currentNode->coords + (Direction)i),0);
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
                    }*/
                }
                Node * neighbor = currentNode->neighbors[i];

                if(!neighbor->closed)
                {
                    int gScore = currentNode->gScore + 1;
                    neighbor->hScore = neighbor->coords.distance(endPosition);
                    bool beenVisited = neighbor->visited;

                    if(!neighbor->visited || gScore < neighbor->gScore)
                    {
                        neighbor->visited = true;
                        neighbor->parent = currentNode;

                        if(!beenVisited)
                        {
                            //openList.emplace(std::make_pair(Positionf(neighbor->coords, neighbor->fScore()),neighbor));
                            openList.push_back(neighbor);
                        }
                    }

                }
            }
        }
    }
    return std::vector<Direction>(); //No path found
}

Node* Graph::findNode(std::vector<Node *> list, Position pos)
{
    for(int i = 0; i < list.size(); i++)
    {
        if(list[i]->coords == pos)
        {
            return list[i];
        }
    }
    return new Node(pos);
}

