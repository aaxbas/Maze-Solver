#include "Map.hpp"
#include "Screen.hpp"
#include "SDL2/SDL.h"
#include "Tile.hpp"

#include <iostream>
#include <fstream>
#include<string>

const SDL_Color COLOR_BG = {0x00, 0x00, 0x00, 0xFF};
const SDL_Color COLOR_FG = {0xFF, 0xFF, 0xFF, 0xFF};

int main(int argc, char **argv)
{   
    Map m;

    std::ifstream f;
    f.open(std::string(argv[1]));

    if(f)
        m.readMap(std::string(argv[1]));
    else{
        int r,c;
        if (argv[2] && argv[3]){
            r = std::stoi(argv[2]);
            c = std::stoi(argv[3]);
            if(r*c % 64 != 0){
                std::cout << "Rows and columns must be divisible by 64!" << std::endl;
                exit(1);
            }
        }

        m = Map(r*c, r, c);
    }
   
    Screen s = Screen(640, 640, COLOR_FG, COLOR_BG);
    s.InitializeScreen();
    s.rescale(m.rows,m.cols);
    s.DrawScreen(m);

    bool quit = false;
    SDL_Event e;

    bool changed = false, isDragged=false;
    int prevX, prevY, dragtype;
    Tile prevTile;

    while (!quit)
    {
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP)
            {
                //Get mouse position
                int x, y;
                SDL_GetMouseState( &x, &y );
                if (x >= 0 && y >= 0 && x <= 640 && y <= 640)
                {   

                    /**
                    if (changed){
                        m.map[prevY][prevX] = prevTile;
                    }**/

                    s.mouseToScreen(&x, &y);
                    
                    prevX = x;
                    prevY = y;
                    prevTile = m.map[y][x];

                    //m.map[y][x].type = 4;
                    s.DrawScreen(m);
                    changed = true;

                    if(e.type == SDL_MOUSEBUTTONDOWN || isDragged){
                        int nextType = m.map[y][x].type;
                        if(nextType > 2)
                            nextType = 0;
                        else
                            nextType++;
                        
                        if(!isDragged)
                            dragtype = nextType;
                        else 
                            nextType = dragtype;

                        m.map[y][x].type = nextType;
                       
                        if(nextType == 2){
                            m.goal = {x,y};
                        }
                        else if (nextType == 3)
                            m.start = {x,y};


                        s.DrawScreen(m);
                        isDragged = true;
                    }

                    if (e.type == SDL_MOUSEBUTTONUP){
                        isDragged = false;
                    }
                
                }

            }
            if (e.type == SDL_QUIT){
                quit = true;
            }

            if (e.type == SDL_KEYDOWN)
                m.writeMap(argv[1]);
        }
        SDL_Delay(100);
    }
}


