#include <SDL.h>
#include "mazes.h"

// chnange map
#define WIDTH WIDTH6
#define HEIGHT HEIGHT6
#define maze maze6
int pacmanX =  MAZE6_START_X;
int pacmanY = MAZE6_START_Y;


#define TILE_SIZE 20



void renderMaze(SDL_Renderer* renderer) {
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
            else if (maze[row][col] == 0) {
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);  // Black
                SDL_RenderFillRect(renderer, &tile);
            }
        }
    }
}

void renderPacman(SDL_Renderer* renderer) {
    SDL_Rect pacmanTile;
    pacmanTile.x = pacmanX * TILE_SIZE;
    pacmanTile.y = pacmanY * TILE_SIZE;
    pacmanTile.w = TILE_SIZE;
    pacmanTile.h = TILE_SIZE;

    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);  
    SDL_RenderFillRect(renderer, &pacmanTile);
}


#define speed 9
int speedCounter = speed;
int dx = 0;
int dy = 0;


void updatePacmanPosition() {
    if (speedCounter <= 0) {
        int newX = pacmanX+dx;
        int newY = pacmanY+dy;
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
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow("PacmanMaze", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, TILE_SIZE * WIDTH, TILE_SIZE * HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);


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
        renderMaze(renderer);
        renderPacman(renderer);
        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
