#include "graph.h"

Graph::Graph()
{

}

Graph::~Graph()
{

}

std::vector<Direction> Graph::findPath(World * world, Position startPosition, Position endPosition)
{
    Node * start = new Node(startPosition, endPosition, 0);
    std::priority_queue<Node*, std::vector<Node*>, CompareNode> nextToVisit = std::priority_queue<Node*, std::vector<Node*>, CompareNode>();
    QHash<Position, Node*> visitedNodes = QHash<Position, Node*>();

    nextToVisit.push(start);

    while(!nextToVisit.empty())
    {
        //Take the node with the lowest F score, move it from the priority queue to the list of visited nodes
        Node * currentNode = nextToVisit.top();
        nextToVisit.pop();
        visitedNodes.insert(currentNode->coords, currentNode);

        //Check if this is the destination
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

        //If we're not there yet, check the neighbors and add them to the queue
        for(int i = 0; i < 6; i++)
        {
            if(world->canGo(currentNode->coords, (Direction)i))
            {
                Node * neighbor;
                if(currentNode->neighbors[i] == 0) //If the neighbor isn't set
                {
                    //First check if it exists in the list of nodes
                    Position targetCoords = currentNode->coords + (Direction)i;
                    if(visitedNodes.contains(targetCoords))
                    {
                        currentNode->neighbors[i] = visitedNodes[targetCoords];
                    }
                    else //it doesn't exist yet
                    {
                        //Create the node
                        Node * newNode = new Node(targetCoords, endPosition, currentNode);

                        //Set it as the neighbor
                        currentNode->neighbors[i] = newNode;
                        neighbor = newNode;

                        //Visit it later
                        nextToVisit.push(newNode);
                    }
                }
                else
                {
                    neighbor = currentNode->neighbors[i];
                }
            }
        }
    }

    return std::vector<Direction>(); //No path found
}

