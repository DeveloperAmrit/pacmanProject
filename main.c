#include <SDL.h>
#include "mazes.h"
#include "utils.h"
#include "mainFunctions.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "screenchanging.h"

int main(int argc, char* argv[])
{   
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
    TTF_Init();

    int mapNumber = 0;

    while (screenNumber != -1) {
        switch (screenNumber) {
        case 0:
            screenNumber = welcomescreen();
            break;
        case 1:
            mapNumber =  selectMap();
            break;
        case 2:
            score = mainGame(mapNumber);
            break;
        case 3:
            gameOver(score,isHighScore);
            break;
        case 4:
            // showHighScore();
            printf("In Contruction");
            screenNumber = -1;
            break;
        }
    }

    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}