#pragma once
#ifndef MAINFUNCTIONS_H
#define MAINFUNCTIONS_H


extern int ghostsX[];
extern int ghostsY[];
extern int ghostSpeedCounterarr[];
extern int gdxarr[];
extern int gdyarr[];



// generalized functions
void renderTexture(SDL_Renderer* renderer, int x, int y, SDL_Texture* Texture, int angle, int TILE_SIZE);
void drawItem(SDL_Renderer* renderer, int x, int y, int radius, SDL_Color color);
void calculateABTAS(int HEIGHT, int WIDTH, int** maze, int* ABTAS);
void randomItemPlacer(int total, int value, int* restrictedValues, int lengthOfresvalsarr, int*ABTAS, int HEIGHT, int WIDTH, int** maze);

//point calculation
void calculatePoint(int** maze, int WIDTH, int pacmanX, int pacmanY, int* points);

//rendering
void showPoint(SDL_Renderer* renderer, int score, int x, int y);
void renderMaze(SDL_Renderer* renderer, SDL_Texture* cherryTexture, int TILE_SIZE, int WIDTH, int HEIGHT, int** maze, int SMALL_DOT_RADIUS, SDL_Color dotColor);
void renderPacman(SDL_Renderer* renderer, SDL_Texture* pacmanOMTexture, SDL_Texture* pacmanCMTexture, int TILE_SIZE, int pacmanX, int pacmanY, int dx, int dy, int timeCounter);
void renderGhosts(SDL_Renderer* renderer, SDL_Texture** arrayOfTextures, int total, int TILE_SIZE, int NUMOFGHOSTS);

// pacman movement
void updatePacmanPosition(int HEIGHT, int WIDTH, int** maze, int SPEED, int* speedCounter, int* pacmanX, int* pacmanY, int dx, int dy);
void setDirection(int direction, int* dx_, int* dy_);

// ghost movement
void moveGhostRandomly(int* gx, int* gy, int* gdx, int* gdy, int* ghostSpeedCounter, int ghostSpeed, int HEIGHT, int WIDTH, int** maze);
void ghostMovement(int NUMOFGHOSTS, int maxdistacnetochase, int pacmanX, int pacmanY, int ghostSpeed, int HEIGHT, int WIDTH, int** maze);

// collision
int isCollided(int NUMOFGHOSTS, int pacmanX, int pacmanY, int points);


#endif
