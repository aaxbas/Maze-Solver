#include "Screen.hpp"
#include "SDL2/SDL.h"
#include "Map.hpp"
#include <iostream>

Screen::Screen(int w, int h, SDL_Color bg, SDL_Color fg)
{
    width = w;
    height = h;
    empty = bg;
    wall = fg;
    quit = false;
}

Screen::~Screen()
{

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    window = NULL;
    renderer = NULL;
    SDL_Quit();
}

/**
 *  @brief Initialize SDL2 screen and sound settings
*/
void Screen::InitializeScreen()
{

    window = NULL;
    renderer = NULL;

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "SDL could not initialize! SDL_Error: " << std::endl
                  << SDL_GetError();
    }
    else
    {
        // Set texture filtering to linear
        if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
        {
            std::cout << "Warning: Linear texture filtering not enabled!" << std::endl;
        }

        // Create window
        window = SDL_CreateWindow("Maze", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
        if (window == NULL)
        {
            std::cout << "Window could not be created! SDL_Error:" << std::endl
                      << SDL_GetError();
        }
        else
        {
            // Create window renderer
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

            if (renderer == NULL)
            {
                std::cout << "Renderer could not be created! SDL Error: " << std::endl
                          << SDL_GetError();
            }

            SDL_RenderSetScale(renderer, 80, 80);
            SDL_SetRenderDrawColor(renderer, empty.r, empty.g, empty.b, empty.a);
            SDL_RenderClear(renderer);

            SDL_RenderPresent(renderer);
        }
    }
}

/**
 * @brief Set SDL renderer scale to match map rows and cols
 * @param r the number of rows
 * @param c the number of cols
 * @warning the rows and cols must be divisible by the width and height respectively
 */ 
void Screen::rescale(int r, int c){
    if(width % r != 0 || height % c != 0){
        std::cerr << "The rows and cols must be divisible by the width and height respectively!" << std::endl;
        exit(1);
    }

    scaleX = width/r;
    scaleY = height/c;
    SDL_RenderSetScale(renderer, scaleX, scaleY);
}

/**
*   @brief Update renderers to display new screen
*   @param m the Map to render
*/
void Screen::DrawScreen(Map m)
{
    
    for (int x = 0; x < m.rows; x++)
    {
        for (int y = 0; y < m.cols; y++)
        {   
            switch (m.map[x][y].type)
            {
            case 1:
                SDL_SetRenderDrawColor(renderer, wall.r, wall.g, wall.b, wall.a);
                SDL_RenderDrawPoint(renderer, y, x);
                break;
            case 2:
                SDL_SetRenderDrawColor(renderer, goal.r, goal.g, goal.b, goal.a);
                SDL_RenderDrawPoint(renderer, y, x);
                break;
            case 3:
                SDL_SetRenderDrawColor(renderer, start.r, start.g, start.b, start.a);
                SDL_RenderDrawPoint(renderer, y, x);
                break;
            case 4:
                SDL_SetRenderDrawColor(renderer, select.r, select.g, select.b, select.a);
                SDL_RenderDrawPoint(renderer, y, x);
                break;
            case 5:
                SDL_SetRenderDrawColor(renderer, select.r, select.g, select.b, select.a);
                SDL_RenderDrawPoint(renderer, y, x);
                break;
            case 6:
                SDL_SetRenderDrawColor(renderer, path.r, path.g, path.b, path.a);
                SDL_RenderDrawPoint(renderer, y, x);
                break;
            default:
                SDL_SetRenderDrawColor(renderer, empty.r, empty.g, empty.b, empty.a);
                SDL_RenderDrawPoint(renderer, y, x);
                break;
            }
            
        }
    }

    SDL_RenderPresent(renderer);
}

/**
 * @brief Convert mouse coordinates to screen/map coordinates
 * @param[out] x the x coordinate
 * @param[out] y the y coordinate
 */ 
void Screen::mouseToScreen(int *x, int *y){
    *x /= scaleX;
    *y /= scaleY;
}

void Screen::eventHandler(){
    SDL_Event e;

    while(SDL_PollEvent(&e) != 0){
       if (e.type == SDL_QUIT){
            std::cout << "Exiting!" << std::endl;
            exit(0);
        }
    }
}

void Screen::delay(int ms){
    SDL_Delay(ms);
}