#include <SDL.h>
#include "mazes.h"
#include "utils.h"
#include "mainFunctions.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string.h>
#include "screenchanging.h"

int screenNumber = 0;

int mainGame(int mapNumber) {

    // setting all map variables
    
    // tile size
    const int TILE_SIZE = 20;

    // map
    int WIDTH = mapsCols[mapNumber];
    int HEIGHT = mapsRows[mapNumber];

    int** maze = (int**)malloc(HEIGHT * sizeof(int*));  
    for (int i = 0; i < HEIGHT; i++) {
        maze[i] = (int*)malloc(WIDTH * sizeof(int));
    }
    
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            maze[y][x] = maps[mapNumber][y*WIDTH+x];
        }
    }

    int pacmanX = mapsPacmanStartX[mapNumber];
    int pacmanY = mapsPacmanStartY[mapNumber];

    const int NUMOFGHOSTS = mapsNumOfGhosts[mapNumber];

    // pacman movement
    #define SPEED 7
    int speedCounter = 0;
    int dx = 0;
    int dy = 0;
    int timeCounter = 0;

    // point dots
    #define SMALL_DOT_RADIUS 1
    SDL_Color dotColor = { 100,100,100,100 };

    // random function seed
    int ABTAS = -1;

    // score
    int score = -1;

    // ghosts
    #define ghostSpeed 10
    int _tempmaxdtc_ = HEIGHT * WIDTH / 130;
    const int maxdistacnetochase = (_tempmaxdtc_ < 2) ? 2 : _tempmaxdtc_;

    // window
    const int windowWidth = WIDTH*TILE_SIZE;
    const int windowHeight = HEIGHT*TILE_SIZE+20;


    copyArray(ghostsX, mapsAllGhostsX[mapNumber], (int)NUMOFGHOSTS);
    copyArray(ghostsY, mapsAllGhostsY[mapNumber], (int)NUMOFGHOSTS);
    for (int i = 0;i < NUMOFGHOSTS;i++) {
        gdxarr[i] = 1;
        gdyarr[i] = 0;
        ghostSpeedCounterarr[i] = 0;
    }



    SDL_Window* window = SDL_CreateWindow("PacmanMaze", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowWidth, windowHeight, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, 1, SDL_RENDERER_ACCELERATED);

    // loading media
    SDL_Surface* cherrySurface = IMG_Load("./assets/pacmancherry.png");
    SDL_Texture* cherryTexture = SDL_CreateTextureFromSurface(renderer, cherrySurface);
    SDL_FreeSurface(cherrySurface);

    SDL_Surface* pacmanOMSurface = IMG_Load("./assets/pacman1.png");
    SDL_Texture* pacmanOMTexture = SDL_CreateTextureFromSurface(renderer, pacmanOMSurface);
    SDL_FreeSurface(pacmanOMSurface);

    SDL_Surface* pacmanCMSurface = IMG_Load("./assets/pacman2.png");
    SDL_Texture* pacmanCMTexture = SDL_CreateTextureFromSurface(renderer, pacmanCMSurface);
    SDL_FreeSurface(pacmanCMSurface);

    SDL_Surface* ghost1Surface = IMG_Load("./assets/pacmanghost1.png");
    SDL_Texture* ghost1Texture = SDL_CreateTextureFromSurface(renderer, ghost1Surface);
    SDL_FreeSurface(ghost1Surface);

    SDL_Surface* ghost2Surface = IMG_Load("./assets/pacmanghost2.png");
    SDL_Texture* ghost2Texture = SDL_CreateTextureFromSurface(renderer, ghost2Surface);
    SDL_FreeSurface(ghost2Surface);

    SDL_Surface* ghost3Surface = IMG_Load("./assets/pacmanghost3.png");
    SDL_Texture* ghost3Texture = SDL_CreateTextureFromSurface(renderer, ghost3Surface);
    SDL_FreeSurface(ghost3Surface);

    SDL_Surface* ghost4Surface = IMG_Load("./assets/pacmanghost4.png");
    SDL_Texture* ghost4Texture = SDL_CreateTextureFromSurface(renderer, ghost4Surface);
    SDL_FreeSurface(ghost4Surface);

    SDL_Surface* ghost5Surface = IMG_Load("./assets/pacmanghost5.png");
    SDL_Texture* ghost5Texture = SDL_CreateTextureFromSurface(renderer, ghost5Surface);
    SDL_FreeSurface(ghost5Surface);

    SDL_Surface* ghost6Surface = IMG_Load("./assets/pacmanghost6.png");
    SDL_Texture* ghost6Texture = SDL_CreateTextureFromSurface(renderer, ghost6Surface);
    SDL_FreeSurface(ghost6Surface);

    SDL_Texture* ghoststextures[6] = { ghost1Texture,ghost2Texture,ghost3Texture,ghost4Texture,ghost5Texture,ghost6Texture };

    calculateABTAS(HEIGHT,WIDTH,maze,&ABTAS);

    // for cheery
    int rs1[3] = { 1, 0, 3 };
    randomItemPlacer(HEIGHT * WIDTH / 90, 3, rs1, 3,&ABTAS,HEIGHT,WIDTH,maze);

    // time counter
    int lastUpdate = SDL_GetTicks(); // Track time of the last update
    int updateInterval = SPEED * 8;

    int a = 0;

    SDL_Event event;
    int running = 1;
    while (running)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                screenNumber = -1;
                running = 0;
            }
            else if (event.type == SDL_KEYDOWN)
            {
                switch (event.key.keysym.sym)
                {
                case SDLK_UP:
                    setDirection(1, &dx, &dy);
                    break;
                case SDLK_DOWN:
                    setDirection(2, &dx, &dy);
                    break;
                case SDLK_LEFT:
                    setDirection(3, &dx, &dy);
                    break;
                case SDLK_RIGHT:
                    setDirection(4, &dx, &dy);
                    break;
                case SDLK_s:
                    setDirection(2, &dx, &dy);
                    break;
                case SDLK_a:
                    setDirection(3, &dx, &dy);
                    break;
                case SDLK_d:
                    setDirection(4, &dx, &dy);
                    break;
                case SDLK_w:
                    setDirection(1, &dx, &dy);
                    break;
                }

            }
        }

        updatePacmanPosition(HEIGHT,WIDTH,maze,SPEED,&speedCounter,&pacmanX,&pacmanY,dx,dy);
        ghostMovement(NUMOFGHOSTS, maxdistacnetochase,pacmanX,pacmanY, ghostSpeed,HEIGHT,WIDTH,maze);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        renderMaze(renderer, cherryTexture,TILE_SIZE,WIDTH,HEIGHT,maze,SMALL_DOT_RADIUS,dotColor);
        renderPacman(renderer, pacmanOMTexture, pacmanCMTexture,TILE_SIZE,pacmanX,pacmanY,dx,dy,timeCounter);
        renderGhosts(renderer, ghoststextures, NUMOFGHOSTS,TILE_SIZE,NUMOFGHOSTS);
        calculatePoint(maze,WIDTH,pacmanX,pacmanY,&score);
        showPoint(renderer, score, 10, HEIGHT * TILE_SIZE);
        SDL_RenderPresent(renderer);
        if (isCollided(NUMOFGHOSTS,pacmanX,pacmanY,score)) {
            break;
        }
        SDL_Delay(16);
        int currentTime = SDL_GetTicks();
        if (currentTime - lastUpdate >= updateInterval)
        {
            timeCounter++;
            lastUpdate = currentTime; // Reset last update time
        }
    }
    SDL_DestroyTexture(cherryTexture);
    SDL_DestroyTexture(pacmanOMTexture);
    SDL_DestroyTexture(pacmanCMTexture);
    SDL_DestroyTexture(ghost1Texture);
    SDL_DestroyTexture(ghost2Texture);
    SDL_DestroyTexture(ghost3Texture);
    SDL_DestroyTexture(ghost4Texture);
    SDL_DestroyTexture(ghost5Texture);
    SDL_DestroyTexture(ghost6Texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    return score;
}

int welcomescreen() {
    int SCREEN_WIDTH = 800;
    int SCREEN_HEIGHT = 600;

    SDL_Window* win = SDL_CreateWindow("Pacman", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer* ren = SDL_CreateRenderer(win, 1, SDL_RENDERER_ACCELERATED);

    SDL_Surface* bgs = IMG_Load("./assets/pacmanwallpaper1.jpg");
    SDL_Texture* bg = SDL_CreateTextureFromSurface(ren, bgs);
    SDL_FreeSurface(bgs);

    SDL_Surface* surPlayButton = IMG_Load("./assets/playbtn.png");
    SDL_Texture* texPlayButton = SDL_CreateTextureFromSurface(ren, surPlayButton);
    SDL_FreeSurface(surPlayButton);
    SDL_Surface* surHighScore = IMG_Load("./assets/high.png");
    SDL_Texture* texHighScore = SDL_CreateTextureFromSurface(ren, surHighScore);
    SDL_FreeSurface(surHighScore);
    SDL_Surface* surPacman1 = IMG_Load("./assets/pacman1.png");
    SDL_Texture* texPacman1 = SDL_CreateTextureFromSurface(ren, surPacman1);
    SDL_FreeSurface(surPacman1);
    SDL_Surface* surPacman2 = IMG_Load("./assets/pacman2.png");
    SDL_Texture* texPacman2 = SDL_CreateTextureFromSurface(ren, surPacman2);
    SDL_FreeSurface(surPacman2);
    SDL_Surface* surhead = IMG_Load("./assets/name21.png");
    SDL_Texture* texhead = SDL_CreateTextureFromSurface(ren, surhead);
    SDL_FreeSurface(surhead);
    SDL_Surface* surg1 = IMG_Load("./assets/pacmanghost1.png");
    SDL_Texture* texg1 = SDL_CreateTextureFromSurface(ren, surg1);
    SDL_FreeSurface(surg1);
    SDL_Surface* surg2 = IMG_Load("./assets/pacmanghost2.png");
    SDL_Texture* texg2 = SDL_CreateTextureFromSurface(ren, surg2);
    SDL_FreeSurface(surg2);
    SDL_Surface* surg3 = IMG_Load("./assets/pacmanghost3.png");
    SDL_Texture* texg3 = SDL_CreateTextureFromSurface(ren, surg3);
    SDL_FreeSurface(surg3);
    SDL_Rect rectPlayButton = { SCREEN_WIDTH/2-200, SCREEN_HEIGHT-100, 400, 100 };
    SDL_Rect rectHighScore = { 0,SCREEN_HEIGHT-100, 100, 100 };
    SDL_Rect rectPacman1 = { 90, 110, 200, 200 };
    SDL_Rect rectPacman2 = { 90, 110, 200, 200 };
    SDL_Rect recthead = { 250, 10, 300, 100 };
    int z = z = -3;
    int run = 1;
    int t = 0;
    SDL_Event event;
    while (run) {
        SDL_Rect rectghost1 = { 400 + z * 10, 110, 200, 200 };
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                screenNumber = -1;
                run = 0;
            }
            else if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
                int x = event.button.x;
                int y = event.button.y;
                if (x > rectPlayButton.x && x < rectPlayButton.x+ rectPlayButton.w && y > rectPlayButton.y && y < rectPlayButton.y + rectPlayButton.h) {
                    SDL_DestroyTexture(texPlayButton);
                    SDL_DestroyTexture(texHighScore);
                    SDL_DestroyTexture(texPacman1);
                    SDL_DestroyTexture(texPacman2);
                    SDL_DestroyRenderer(ren);
                    SDL_DestroyWindow(win);
                    return 1;
                }
                else {
                    if (x > rectHighScore.x && x < rectHighScore.x + rectHighScore.w && y>rectHighScore.y && y < rectHighScore.y + rectHighScore.h) {
                        SDL_DestroyTexture(texPlayButton);
                        SDL_DestroyTexture(texHighScore);
                        SDL_DestroyTexture(texPacman1);
                        SDL_DestroyTexture(texPacman2);
                        SDL_DestroyRenderer(ren);
                        SDL_DestroyWindow(win);
                        return 4;
                    }
                }
            }
        }

        SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
        SDL_RenderClear(ren);
        SDL_RenderCopy(ren, bg, NULL, NULL);
        SDL_RenderCopyEx(ren, texPlayButton, NULL, &rectPlayButton, 0, NULL, SDL_FLIP_NONE);

        if (t % 30 < 15) {
            SDL_RenderCopyEx(ren, texPacman1, NULL, &rectPacman1, 0, NULL, SDL_FLIP_NONE);
        }
        else {
            SDL_RenderCopyEx(ren, texPacman2, NULL, &rectPacman2, 0, NULL, SDL_FLIP_NONE);
        }
        if (t % 90 < 30) {
            SDL_RenderCopyEx(ren, texg1, NULL, &rectghost1, 0, NULL, SDL_FLIP_NONE);

        }
        else if (t % 90 < 60) {
            SDL_RenderCopyEx(ren, texg2, NULL, &rectghost1, 0, NULL, SDL_FLIP_NONE);

        }
        else {
            SDL_RenderCopyEx(ren, texg3, NULL, &rectghost1, 0, NULL, SDL_FLIP_NONE);

        }

        SDL_RenderCopyEx(ren, texHighScore, NULL, &rectHighScore, 0, NULL, SDL_FLIP_NONE);
        SDL_RenderCopyEx(ren, texhead, NULL, &recthead, 0, NULL, SDL_FLIP_NONE);

        SDL_RenderPresent(ren);
        t++;
        if (t % 20 == 0) {
            z++;
            if (z > 5) {
                z = -4;
            }
        }
        SDL_Delay(16);
    }
    SDL_DestroyTexture(texPlayButton);
    SDL_DestroyTexture(texHighScore);
    SDL_DestroyTexture(texPacman1);
    SDL_DestroyTexture(texPacman2);
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);

    return 0;
}

int selectMap() {
    int SCREEN_WIDTH = 800;
    int SCREEN_HEIGHT = 600;
    SDL_Window* window = SDL_CreateWindow("./assets/Pacman", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, 1, SDL_RENDERER_ACCELERATED);


    SDL_Surface* bgs = IMG_Load("./assets/pacmanwallpaper2.jpg");
    SDL_Texture* bg = SDL_CreateTextureFromSurface(renderer, bgs);
    SDL_FreeSurface(bgs);


    SDL_Surface* mapbtn1s = IMG_Load("./assets/mapbtn1.png");
    SDL_Texture* mapbtn1 = SDL_CreateTextureFromSurface(renderer, mapbtn1s);
    SDL_FreeSurface(mapbtn1s);

    SDL_Surface* mapbtn2s = IMG_Load("./assets/mapbtn2.png");
    SDL_Texture* mapbtn2 = SDL_CreateTextureFromSurface(renderer, mapbtn2s);
    SDL_FreeSurface(mapbtn2s);

    SDL_Surface* mapbtn3s = IMG_Load("./assets/mapbtn3.png");
    SDL_Texture* mapbtn3 = SDL_CreateTextureFromSurface(renderer, mapbtn3s);
    SDL_FreeSurface(mapbtn3s);

    SDL_Surface* mapbtn4s = IMG_Load("./assets/mapbtn4.png");
    SDL_Texture* mapbtn4 = SDL_CreateTextureFromSurface(renderer, mapbtn4s);
    SDL_FreeSurface(mapbtn4s);

    SDL_Surface* mapbtn5s = IMG_Load("./assets/mapbtn5.png");
    SDL_Texture* mapbtn5 = SDL_CreateTextureFromSurface(renderer, mapbtn5s);
    SDL_FreeSurface(mapbtn5s);

    SDL_Surface* mapbtn6s = IMG_Load("./assets/mapbtn6.png");
    SDL_Texture* mapbtn6 = SDL_CreateTextureFromSurface(renderer, mapbtn6s);
    SDL_FreeSurface(mapbtn6s);

    SDL_Texture* mapbtnTextures[] = {mapbtn1, mapbtn2, mapbtn3, mapbtn4, mapbtn5, mapbtn6};

    int BUTTON_WIDTH = 100;
    int BUTTON_HEIGHT = 100;
    int BUTTON_GAP_X = (SCREEN_WIDTH - 3 * BUTTON_WIDTH) / 4;
    int BUTTON_GAP_Y = (SCREEN_HEIGHT - 2 * BUTTON_HEIGHT) / 3;

    // change here if changing number of maps
    SDL_Rect rect[6];
    for (int i = 0;i < 6;i++) {                                  
        rect[i].x = (i%3)*BUTTON_WIDTH + (i%3+1)*BUTTON_GAP_X;
        rect[i].y = (i/3)*BUTTON_HEIGHT + (i/3+1) * BUTTON_GAP_Y;
        rect[i].w = BUTTON_WIDTH;
        rect[i].h = BUTTON_HEIGHT;
    }

    SDL_Event event;
    int running = 1;
    while (running) {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                screenNumber = -1;
                running = 0;
            }
            else if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
                int x = event.button.x;
                int y = event.button.y;
                
                int mapNumber = -1;
                for (int i = 0;i < 6;i++) {
                    if (x > rect[i].x && x < rect[i].x + rect[i].w && y > rect[i].y && y < rect[i].y + rect[i].h) {
                        mapNumber = i;
                        for (int j = 0;j < 6;j++) {
                            SDL_DestroyTexture(mapbtnTextures[j]);
                        }
                        SDL_DestroyRenderer(renderer);
                        SDL_DestroyWindow(window);
                        screenNumber = 2;
                        return mapNumber;

                    }
                }
            }
        }
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, bg, NULL, NULL);
        for (int i = 0;i < 6;i++) {
            SDL_RenderCopy(renderer, mapbtnTextures[i], NULL, &rect[i]);
        }
        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    for (int i = 0;i < 6;i++) {
        SDL_DestroyTexture(mapbtnTextures[i]);
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    return 0;
}   