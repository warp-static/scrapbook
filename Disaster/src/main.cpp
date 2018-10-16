#include <iostream>
#include <SDL2/SDL.h>
#include <fstream>
#include <string>
#include "res_path.h"
#include <vector>

#define fps 60

#undef main

int main()
{
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window* window = NULL;

    window = SDL_CreateWindow("Disaster", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1187, 627, SDL_WINDOW_RESIZABLE | SDL_WINDOW_BORDERLESS);

    if(!window)
    {
        std::cout << "failed to create SDL window" << std::endl << SDL_GetError() << std::endl;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, 1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    unsigned int starting_tick;
    bool running = true;
    SDL_Event e;

    float pos = 593;
    float vel = 0, acc = 0;
    bool accelerating;

    std::vector<SDL_Rect> bullets;
    unsigned int bullet_time = 0;

    SDL_Rect rectangle = {pos, 610, 5, 8};

    const Uint8 *keys = SDL_GetKeyboardState(NULL);

    while(running)
    {
        starting_tick = SDL_GetTicks();

        while(SDL_PollEvent(&e))
        {
            if(e.type == SDL_QUIT || e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)
            {
                running = false;
                break;
            }
        }

        accelerating = false;
        if (keys[SDL_SCANCODE_LEFT])
        {
            acc -= 0.1;
            if(acc < -5) acc = -5;
            accelerating = true;
        }
        if (keys[SDL_SCANCODE_RIGHT])
        {
            acc += 0.1;
            if(acc > 5) acc = 5;
            accelerating = true;
        }
        if(accelerating)
        {
            vel += acc;
            if(vel < -15) vel = -15; else if(vel > 15) vel = 15;
        }
        else
        {
            acc = 0;
            vel /= 1.2;
        }
        pos += vel;

        if (keys[SDL_SCANCODE_LCTRL])
        {
            if(SDL_GetTicks() - bullet_time >= 300)
            {
                bullet_time = SDL_GetTicks();
                bullets.push_back({(int)pos, 610, 1, 1});
            }
        }

        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x22, 0x88);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderFillRect(renderer, &rectangle);

        rectangle.x = pos;

        if(!bullets.empty())
        {
            for(int i=0; i<bullets.size(); i++)
            {
                bullets[i].y -= 5;
                SDL_RenderFillRect(renderer, &bullets[i]);
            }
        }

        SDL_RenderPresent(renderer);

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