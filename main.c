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
    int mapNumber = 5;
    int score = -1;
    while (screenNumber != -1) {
        switch (screenNumber) {
        case 0:
            screenNumber = welcomescreen();
            break;
        case 1:
            //mapNumber =  selectMap();
            printf("In Contruction");
            screenNumber = -1;
            break;
        case 2:
            score = mainGame(mapNumber);
            break;
        case 3:
            //gameOver(score);
            printf("In Contruction");
            screenNumber = -1;
            break;
        case 4:
            // showHighScore();
            printf("In Contruction");
            screenNumber = -1;
            break;
        }
    }
}