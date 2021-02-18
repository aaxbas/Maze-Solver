#include "Dijkstra.hpp"
#include "Tile.hpp"
#include "Map.hpp"
#include "Screen.hpp"

#include <limits>
#include <algorithm>
#include<unistd.h>

/**
 * @brief Solve maze using Dijkstra's algorithm
 * @param map The maze to solve
 */
void Dijkstra::solve(Map* map, Screen* s)
{
    // 11:24

    // Set all distances to inf
    for (auto tv : map->map)
    {
        for (auto t : tv)
            t.distance = std::numeric_limits<int>::max();
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


        if(curr->coordinate == map->goal){
            std::cout << "\nGoal Reached!" << std::endl;
            break;
            return;
        }

        for (Tile neighbour : map->adjUnvisitedTiles(curr->coordinate.x, curr->coordinate.y))
        {
            int min_distance = std::min(curr->distance, neighbour.distance);

            if (min_distance != neighbour.distance){
                neighbour.distance = min_distance;
                std::make_heap(queue.begin(), queue.end());
            }

            map->map[neighbour.coordinate.y][neighbour.coordinate.x].parent = {curr->coordinate.x, curr->coordinate.y};


            if(!findInQueue(queue, neighbour)) {
                queue.push_back(&map->map[neighbour.coordinate.y][neighbour.coordinate.x]);
                std::push_heap(queue.begin(), queue.end());
                //std::make_heap(queue.begin(), queue.end())
            }

            

        }
        
        if(isStep){
            s->delay(stepDelay);
            s->DrawScreen(*map);
        }
    s->eventHandler();
    }
  
    drawPath(map,s);
    
}


bool Dijkstra::findInQueue(std::vector<Tile*> queue, Tile tile){
    for(auto t : queue){
        if(t->coordinate == tile.coordinate)
            return true;
    }
    return false;
}

void Dijkstra::drawPath(Map* m, Screen* s){
    Tile t = m->map[m->goal.y][m->goal.x];
    int a;
    while(t.coordinate != m->start){
    
        m->map[t.parent.y][t.parent.x].type = 6;
        t = m->map[t.parent.y][t.parent.x];
        
        s->eventHandler();
    }
    
    m->map[m->goal.y][m->goal.x].type = 2;
    m->map[m->start.y][m->start.x].type = 3;

    s->DrawScreen(*m);
}
