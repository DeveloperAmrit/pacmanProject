#pragma once
#ifndef MAINFUNCTIONS_H
#define MAINFUNCTIONS_H

// tiles
#define TILE_SIZE 20

// map
#define WIDTH WIDTH3
#define HEIGHT HEIGHT3
#define maze maze3
extern int pacmanX;
extern int pacmanY;

// window dimensions
extern int windowWidth;
extern int windowHeight;

// speed and movement
#define SPEED 7
extern int speedCounter;
extern int dx;
extern int dy;

// time
extern int timeCounter;

// point dots
#define SMALL_DOT_RADIUS 1
extern SDL_Color dotColor;  // Initialize in .c file if used globally

// random function seed
extern int ABTAS;

// points
extern int points;

// generalized functions
void renderTexture(SDL_Renderer* renderer, int x, int y, SDL_Texture* texture, int angle);
void drawItem(SDL_Renderer* renderer, int x, int y, int radius, SDL_Color color);
void calculateABTAS();
void randomItemPlacer(int total, int value, int* restrictedValues, int lengthOfResValsArr);

//point calculation
void calculatePoint();

//rendering
void showPoint(SDL_Renderer* renderer, int score, int x, int y);
void renderMaze(SDL_Renderer* renderer, SDL_Texture* cherryTexture);
void renderPacman(SDL_Renderer* renderer, SDL_Texture* pacmanOMTexture, SDL_Texture* pacmanCMTexture);

// pacman movement
void updatePacmanPosition();
void setDirection(int direction);


#endif
