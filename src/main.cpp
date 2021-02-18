#include "Map.hpp"
#include "Screen.hpp"
#include "SDL2/SDL.h"
#include "Dijkstra.hpp"
#include "Astar.hpp"
#include <iostream>

const SDL_Color COLOR_BG = {0x00, 0x00, 0x00, 0xFF};
const SDL_Color COLOR_FG = {0xFF, 0xFF, 0xFF, 0xFF};

int main(int argc, char **argv)
{
    Map m;
   
    m.readMap(argv[1]);
    m.printMap();

    Screen s = Screen(640, 640, COLOR_FG, COLOR_BG);
    s.InitializeScreen();
    s.rescale(m.rows,m.cols);
    s.DrawScreen(m);
    SDL_Delay(1000);

    
    if(argv[2] == "Dijkstra"){
        Dijkstra solver;
        solver.solve(&m, &s);
    }
    else{
        Dijkstra solver;
        solver.solve(&m, &s);
    }

    
    s.DrawScreen(m);
    
    m.printMap();

    SDL_Delay(5000);
}