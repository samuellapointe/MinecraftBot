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

    std::vector<Node*> openList;

    Node * start = new Node(startPosition);
    start->hScore = start->coords.distance(endPosition);

    openList.push_back(start);

    while(!openList.empty())
    {
        Node * currentNode = openList.front();
        openList.erase(openList.begin());
        //std::make_heap(openList.begin(), openList.end(), CompareNode());
        /*for(int i = 0; i < openList.size(); i++)
        {
            if(openList[i]->fScore() < currentNode->fScore())
            {
                currentNode = openList[i];
            }
        }*/

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

        //openList.erase(std::find(openList.begin(), openList.end(), currentNode));
        currentNode->closed = true;

        //Check neighbors
        for(int i = 0; i < 6; i++)
        {
            if(currentNode->neighbors[i] == 0)
            {
                currentNode->neighbors[i] = new Node(currentNode->coords + (Direction)i);
            }
            Node * neighbor = currentNode->neighbors[i];

            if(world->canGo(currentNode->coords, (Direction)i) && !neighbor->closed)
            {
                int gScore = currentNode->gScore + 1;
                bool beenVisited = neighbor->visited;

                if(!neighbor->visited || gScore < neighbor->gScore)
                {
                    neighbor->visited = true;
                    neighbor->parent = currentNode;
                    neighbor->hScore = neighbor->coords.distance(endPosition);
                    neighbor->gScore = gScore;

                    if(!beenVisited)
                    {
                        openList.push_back(neighbor);
                        std::make_heap(openList.begin(), openList.end(), CompareNode());
                    }
                    else
                    {
                        //std::make_heap(openList.begin(), openList.end(), CompareNode());
                    }
                }

            }
        }
    }
    return std::list<Position>(); //No path found
}

