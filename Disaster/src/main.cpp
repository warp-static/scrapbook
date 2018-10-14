#include <iostream>
#include <SDL2/SDL.h>
#include <fstream>
#include <string>
#include "res_path.h"

#define fps 60

#undef main

int main()
{
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window* window = NULL;

    window = SDL_CreateWindow("Disaster", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1187, 627, SDL_WINDOW_RESIZABLE /*| SDL_WINDOW_BORDERLESS*/);

    if(!window)
    {
        std::cout << "failed to create SDL window" << std::endl << SDL_GetError() << std::endl;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, 1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    unsigned int starting_tick;
    bool running = true;
    SDL_Event e;

    int pos = 593;

    SDL_Rect rectangle = {pos, 610, 5, 8};

    while(running)
    {
        starting_tick = SDL_GetTicks();

        while(SDL_PollEvent(&e))
        {
            if(e.type == SDL_QUIT)
            {
                running = false;
                break;
            }

            SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x22, 0x88);
            SDL_RenderClear(renderer);

            rectangle.x = pos;

            SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
            SDL_RenderFillRect(renderer, &rectangle);

            SDL_RenderPresent(renderer);

            if(e.type == SDL_KEYDOWN)
            {
                switch(e.key.keysym.sym)
                {
                    case SDLK_LEFT:
                    pos -= 10;
                    break;

                    case SDLK_RIGHT:
                    pos += 10;
                    break;
                }
            }
        }

        int frameTime = SDL_GetTicks() - starting_tick;

        if((1000 / fps) > frameTime)
        {
            SDL_Delay((1000 / fps) - frameTime);
        }
    }

    SDL_DestroyRenderer(renderer);

    SDL_DestroyWindow(window);

    SDL_Quit();

    return 0;
}