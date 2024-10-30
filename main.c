#include <SDL.h>
#include "mazes.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL_image.h>

// chnange map
#define WIDTH WIDTH6
#define HEIGHT HEIGHT6
#define maze maze6
int pacmanX = MAZE6_START_X;
int pacmanY = MAZE6_START_Y;

// global variables
// speed and movement
#define speed 7
int speedCounter = speed;
int dx = 0;
int dy = 0;
// time
int timeCounter = 0;

// tile size
#define TILE_SIZE 20

// dots
#define smallDotRadius 1
SDL_Color dotColor = { 200,200,200,200 };

int ABTAS = -1;                // availableBlackTilesAtSpawn

void renderTexture(SDL_Renderer* renderer, int x, int y,SDL_Texture* Texture,int angle) {
    SDL_Rect Rect = { x, y, TILE_SIZE, TILE_SIZE };
    SDL_RenderCopyEx(renderer, Texture, NULL, &Rect,angle,NULL,SDL_FLIP_NONE);
}

void drawItem(SDL_Renderer* renderer,int x,int y,int radius, SDL_Color color) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_Rect dotRect = { x - radius,y - radius,2 * radius,2 * radius };
    SDL_RenderFillRect(renderer, &dotRect);
}


void calculateABTAS() {
    for (int i = 0;i < HEIGHT;i++) {
        for (int j = 0;j < WIDTH;j++) {
            if (maze[i][j] != 1) {
                ABTAS++;
            }
        }
    }
}

void randomItemPlacer(int total,int value, int* restrictedValues,int n_r) {
    for (int z = 0;z < total;z++) {
        int a = randomInt(0, ABTAS);
        int b = 0;
        for (int i = 0;i < HEIGHT;i++) {
            for (int j = 0;j < WIDTH;j++) {
                int v = 1;
                for (int k = 0;k < n_r;k++) {
                    if (maze[i][j] == restrictedValues[k]) {
                        v = 0;
                    }
                }
                if (v) {
                    if (b == a) {
                        maze[i][j] = value;
                        ABTAS--;
                        b = -1;
                        break;
                    }
                    else {
                        b++;
                    }
                }
                
            }
            if (b == -1) { break; }
        }
    }
}

int points = -1;

void calculatePoint() {
    if (maze[pacmanY][pacmanX] == 2) {
        maze[pacmanY][pacmanX] = 0;
        points++;
        printf("\n%d", points);
    }   
    else if (maze[pacmanY][pacmanX] == 3) {
        maze[pacmanY][pacmanX] = 0;
        points+=10;
        printf("\n%d", points);
    }
}


void renderMaze(SDL_Renderer* renderer,SDL_Texture* cherryTexture) {
    for (int row = 0; row < HEIGHT; row++) {
        for (int col = 0; col < WIDTH; col++) {
            SDL_Rect tile;
            tile.x = col * TILE_SIZE;
            tile.y = row * TILE_SIZE;
            tile.w = TILE_SIZE;
            tile.h = TILE_SIZE;

            if (maze[row][col] == 1) {
                SDL_SetRenderDrawColor(renderer, 0, 0, 139, 255);  // Blue
                SDL_RenderFillRect(renderer, &tile);
            }
            else{
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);  // Black
                SDL_RenderFillRect(renderer, &tile);
            }

            if (maze[row][col] == 3) {
                renderTexture(renderer, tile.x, tile.y,cherryTexture,0);
            }
            else if (maze[row][col] == 2) {
                drawItem(renderer, tile.x + TILE_SIZE / 2, tile.y + TILE_SIZE / 2, smallDotRadius, dotColor);
            }
        }
    }
}

void renderPacman(SDL_Renderer* renderer,SDL_Texture* pacmanOMTexture,SDL_Texture* pacmanCMTexture) {
    SDL_Rect pacmanTile;
    pacmanTile.x = pacmanX * TILE_SIZE;
    pacmanTile.y = pacmanY * TILE_SIZE;
    int angle = 0;
    if (dx == 0 && dy == 0) {
        angle = 0;
    }
    else if (dx == 0) {
        angle = (dy == 1) ? 90 : 270;
    }
    else if (dy == 0) {
        angle = (dx == 1) ? 0 : 180;
    }
    if (timeCounter % 2 == 0) {
        renderTexture(renderer, pacmanTile.x, pacmanTile.y, pacmanOMTexture,angle);
    }
    else {
        renderTexture(renderer, pacmanTile.x, pacmanTile.y, pacmanCMTexture,angle);
    }
   
}

void updatePacmanPosition() {
    if (speedCounter <= 0) {
        int newX = pacmanX + dx;
        int newY = pacmanY + dy;
        if (newX >= 0 && newX < WIDTH && newY >= 0 && newY < HEIGHT && maze[newY][newX] != 1) {
            pacmanX = newX;
            pacmanY = newY;
        }
        speedCounter = speed;
    }
    else {
        speedCounter--;
    }

}

void setDirection(int direction) {
    switch (direction) {
    case 1: dx = 0; dy = -1;break;  // Up
    case 2: dx = 0; dy = 1;break;   // Down
    case 3: dx = -1; dy = 0;break;   // Left
    case 4: dx = 1; dy = 0;break;  // Right
    }
}

int main(int argc, char* argv[]) {
    srand(time(0));
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow("PacmanMaze", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, TILE_SIZE * WIDTH, TILE_SIZE * HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // loading media
    SDL_Surface* cherrySurface = IMG_Load("C:/Users/Hp/Pictures/Saved Pictures/pacmancherry.png");
    SDL_Texture* cherryTexture = SDL_CreateTextureFromSurface(renderer, cherrySurface);
    SDL_FreeSurface(cherrySurface);

    SDL_Surface* pacmanOMSurface = IMG_Load("C:/Users/Hp/Pictures/Saved Pictures/pacman1.png");
    SDL_Texture* pacmanOMTexture = SDL_CreateTextureFromSurface(renderer, cherrySurface);
    SDL_FreeSurface(pacmanOMSurface);

    SDL_Surface* pacmanCMSurface = IMG_Load("C:/Users/Hp/Pictures/Saved Pictures/pacman2.png");
    SDL_Texture* pacmanCMTexture = SDL_CreateTextureFromSurface(renderer, cherrySurface);
    SDL_FreeSurface(pacmanCMSurface);

    calculateABTAS();

    // for big dots
    int rs1[3] = { 1,0,3 };
    randomItemPlacer(HEIGHT * WIDTH / 90, 3,rs1,3);

    // time counter
    int lastUpdate = SDL_GetTicks();  // Track time of the last update
    int updateInterval = speed*16*2;

    SDL_Event event;
    int running = 1;
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            }
            else if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                case SDLK_UP:    setDirection(1); break;
                case SDLK_DOWN:  setDirection(2); break;
                case SDLK_LEFT:  setDirection(3); break;
                case SDLK_RIGHT: setDirection(4); break;
                }
            }
        }
        updatePacmanPosition();

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        renderMaze(renderer,cherryTexture);
        renderPacman(renderer, pacmanOMTexture, pacmanCMTexture);
        calculatePoint();
        SDL_RenderPresent(renderer);
        SDL_Delay(16);
        int currentTime = SDL_GetTicks();
        if (currentTime - lastUpdate >= updateInterval) {
            timeCounter++;
            lastUpdate = currentTime;  // Reset last update time
        }
    }
    SDL_DestroyTexture(cherryTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}