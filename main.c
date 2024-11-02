#include <SDL.h>
#include "mazes.h"
#include "utils.h"
#include "mainFunctions.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

int main(int argc, char* argv[])
{
    srand(time(0));
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
    TTF_Init();

    SDL_Window* window = SDL_CreateWindow("PacmanMaze", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowWidth, windowHeight, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // loading media
    SDL_Surface* cherrySurface = IMG_Load("C:/Users/Hp/Pictures/Saved Pictures/pacmancherry.png");
    SDL_Texture* cherryTexture = SDL_CreateTextureFromSurface(renderer, cherrySurface);
    SDL_FreeSurface(cherrySurface);

    SDL_Surface* pacmanOMSurface = IMG_Load("C:/Users/Hp/Pictures/Saved Pictures/pacman1.png");
    SDL_Texture* pacmanOMTexture = SDL_CreateTextureFromSurface(renderer, pacmanOMSurface);
    SDL_FreeSurface(pacmanOMSurface);

    SDL_Surface* pacmanCMSurface = IMG_Load("C:/Users/Hp/Pictures/Saved Pictures/pacman2.png");
    SDL_Texture* pacmanCMTexture = SDL_CreateTextureFromSurface(renderer, pacmanCMSurface);
    SDL_FreeSurface(pacmanCMSurface);

    calculateABTAS();

    // for cheery
    int rs1[3] = { 1, 0, 3 };
    randomItemPlacer(HEIGHT * WIDTH / 90, 3, rs1, 3);

    // time counter
    int lastUpdate = SDL_GetTicks(); // Track time of the last update
    int updateInterval = SPEED * 8;

    SDL_Event event;
    int running = 1;
    while (running)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                running = 0;
            }
            else if (event.type == SDL_KEYDOWN)
            {
                switch (event.key.keysym.sym)
                {
                case SDLK_UP:
                    setDirection(1);
                    break;
                case SDLK_DOWN:
                    setDirection(2);
                    break;
                case SDLK_LEFT:
                    setDirection(3);
                    break;
                case SDLK_RIGHT:
                    setDirection(4);
                    break;
                }
            }
        }

        updatePacmanPosition();

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        renderMaze(renderer, cherryTexture);
        renderPacman(renderer, pacmanOMTexture, pacmanCMTexture);
        calculatePoint();
        showPoint(renderer, points, 10, HEIGHT * TILE_SIZE);
        SDL_RenderPresent(renderer);
        SDL_Delay(16);
        int currentTime = SDL_GetTicks();
        if (currentTime - lastUpdate >= updateInterval)
        {
            timeCounter++;
            lastUpdate = currentTime; // Reset last update time
        }
    }
    SDL_DestroyTexture(cherryTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}