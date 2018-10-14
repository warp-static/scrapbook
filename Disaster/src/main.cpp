#include <iostream>
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <fstream>
#include <glm/glm.hpp>
#include <string>
#include "res_path.h"

#define fps 60

#undef main

int main()
{
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window* window = NULL;

    window = SDL_CreateWindow("Disaster", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1187, 627, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL /*| SDL_WINDOW_BORDERLESS*/);

    if(!window)
    {
        std::cout << "failed to create SDL window" << std::endl << SDL_GetError() << std::endl;
    }

    SDL_GLContext glcontext = SDL_GL_CreateContext(window);

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED/* | SDL_RENDERER_PRESENTVSYNC*/);

    GLenum res = glewInit();

    glClearColor(0, 0, 0.1, 0.5);

    GLuint program = glCreateProgram();
    GLuint vShader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);

    std::string line;
    std::ifstream vsFile;
    std::string shaderPath = getResourcePath("Disaster") + "basicShader.vs";
    vsFile.open(shaderPath.c_str());
    std::string vsFileText;
    while(vsFile.good())
    {
        getline(vsFile, line);
        vsFileText.append(line + "\n");
    }
    std::ifstream fsFile;
    shaderPath = getResourcePath("Disaster") + "basicShader.fs";
    fsFile.open(shaderPath.c_str());
    std::string fsFileText;
    while(fsFile.good())
    {
        getline(fsFile, line);
        fsFileText.append(line + "\n");
    }

    const GLchar* vsText[1];
    const GLchar* fsText[1];
    GLint vsTextLength[1];
    GLint fsTextLength[1];
    vsText[0] = vsFileText.c_str();
    fsText[0] = fsFileText.c_str();
    vsTextLength[0] = vsFileText.length();
    fsTextLength[0] = fsFileText.length();

    glShaderSource(vShader, 1, vsText, vsTextLength);
    glShaderSource(fShader, 1, fsText, fsTextLength);
    glCompileShader(vShader);
    glCompileShader(fShader);

    glAttachShader(program, vShader);
    glAttachShader(program, fShader);

    glBindAttribLocation(program, 0, "position");

    glLinkProgram(program);
    glValidateProgram(program);
    glUseProgram(program);

    glm::vec3 triangle[] = {
        glm::vec3(-0.5, -0.5, 0),
        glm::vec3(0, 0.5, 0),
        glm::vec3(0.5, -0.5, 0)
    };
    GLuint vertexArray;
    GLuint vertexBuffers[1];
    unsigned int drawCount = 3;
    glGenVertexArrays(1, &vertexArray);
    glBindVertexArray(vertexArray);

    glGenBuffers(1, vertexBuffers);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffers[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangle), triangle, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindVertexArray(0);

    unsigned int starting_tick;
    bool running = true;
    SDL_Event e;

    int pos = 593;

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
            glClear(GL_COLOR_BUFFER_BIT);

            glBindVertexArray(vertexArray);
            glDrawArrays(GL_TRIANGLES, 0, drawCount);
            glBindVertexArray(0);

            SDL_GL_SwapWindow(window);

            SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
            // SDL_RenderClear(renderer);

            SDL_Rect rectangle = {pos, 610, 5, 8};
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

    glDeleteVertexArrays(1, &vertexArray);

    glDetachShader(program, vShader);
    glDeleteShader(vShader);
    glDetachShader(program, fShader);
    glDeleteShader(fShader);

    glDeleteProgram(program);

    SDL_DestroyRenderer(renderer);

    SDL_GL_DeleteContext(glcontext);

    SDL_DestroyWindow(window);

    SDL_Quit();

    return 0;
}