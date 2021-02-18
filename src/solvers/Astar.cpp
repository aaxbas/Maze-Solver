#include "Astar.hpp"
#include "Tile.hpp"
#include "Map.hpp"
#include "Screen.hpp"

#include <limits>
#include <algorithm>
#include<unistd.h>


/**
 * @brief Solve maze using Astar's algorithm
 * @param map The maze to solve
 */
void Astar::solve(Map* map, Screen* s)
{
    // 11:24

    // Set all distances to inf
    for (auto tv : map->map)
    {
        for (auto t : tv){
            t.distance = std::numeric_limits<int>::max();
            t.manhattanD = 2 * (std::abs(map->goal.x - t.coordinate.x) + std::abs(map->goal.y - t.coordinate.y));
        }
        
    }
    std::make_heap(queue.begin(), queue.end());

    // Set the distance of the start pos to 0
    map->map[map->start.y][map->start.x].distance = 0;
    
    queue.push_back(&map->map[map->start.y][map->start.x]);
    std::push_heap(queue.begin(), queue.end());

    
    while (!queue.empty())
    {   
        Tile *curr = queue.front();
        std::pop_heap(queue.begin(), queue.end()); queue.pop_back();
        
        curr->history = true;
        curr->type = 5;

        std::cout  << "Current: " << *curr;

        if(curr->coordinate == map->goal){
            std::cout << "\nGoal Reached!" << std::endl;
            return;
        }

        std::cout << " Adjacent: ";
        for (Tile neighbour : map->adjUnvisitedTiles(curr->coordinate.x, curr->coordinate.y))
        {
            std::cout << neighbour << " ";
            int d = std::min(neighbour.distance, curr->distance + 1);
            int min_distance = std::min(d, neighbour.distance + neighbour.manhattanD);

            if (min_distance != neighbour.distance){
                neighbour.distance = min_distance;
                std::make_heap(queue.begin(), queue.end());
            }

            if(!findInQueue(queue, neighbour)) {
                queue.push_back(&map->map[neighbour.coordinate.y][neighbour.coordinate.x]);
                std::push_heap(queue.begin(), queue.end());
                //std::make_heap(queue.begin(), queue.end())
            }

        }
        
        if(isStep){
            s->DrawScreen(*map);
            usleep(0.25 * 1000000);
        }

        std::cout << std::endl;

        s->eventHandler();

    }
    map->printMap();
}


bool Astar::findInQueue(std::vector<Tile*> queue, Tile tile){
    for(auto t : queue){
        if(t->coordinate == tile.coordinate)
            return true;
    }
    return false;
}