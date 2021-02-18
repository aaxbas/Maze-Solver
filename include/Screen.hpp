#ifndef SCREEN_H
#define SCREEN_H
#include "SDL2/SDL.h"
#include "Map.hpp"



class Screen
{
    public:
        Screen(int w, int h, SDL_Color bg, SDL_Color fg);
        ~Screen();

    private:
        int width;
        int height;
        
        int scaleX, scaleY;

        SDL_Color wall;
        SDL_Color empty;
        SDL_Color correctPath;
        SDL_Color wrongPath;
        SDL_Color goal = {0x00, 0xFF, 0x00, 0xFF};
        SDL_Color start = {0xFF, 0x00, 0x00, 0xFF};
        SDL_Color select = {0x46, 0x46, 0x49, 0x20};
        SDL_Color path = {0x00, 0x00, 0xFF, 0xFF};
        SDL_Window *window;
        SDL_Renderer *renderer;
        SDL_AudioSpec wavSpec;
        SDL_AudioDeviceID deviceId;
        Uint32 wavLength;
        Uint8 *wavBuffer;

    public:
        bool quit;

    public:
        void InitializeScreen();
        void DrawScreen(Map m);
        void rescale(int w, int h);
        void mouseToScreen(int *x, int *y);
        void eventHandler();
        void delay(int ms);
};

#endif /* SCREEN_H */
