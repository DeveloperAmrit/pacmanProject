#include <SDL.h>
#include "mazes.h"
#include "utils.h"
#include "mainFunctions.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

// externs
// map
int pacmanX = MAZE3_START_X;
int pacmanY = MAZE3_START_Y;

// window dimensions
int windowWidth = WIDTH * TILE_SIZE;
int windowHeight = HEIGHT * TILE_SIZE + 24;

// speed and movement
int speedCounter = SPEED;
int dx = 0;
int dy = 0;

// time
int timeCounter = 0;

// point dots
SDL_Color dotColor = { 200, 200, 200, 200 };

// random function seed
int ABTAS = -1;

// points
int points = -1;


// generalised functions

void renderTexture(SDL_Renderer* renderer, int x, int y, SDL_Texture* Texture, int angle)
{
    SDL_Rect Rect = { x, y, TILE_SIZE, TILE_SIZE };
    SDL_RenderCopyEx(renderer, Texture, NULL, &Rect, angle, NULL, SDL_FLIP_NONE);
}

void drawItem(SDL_Renderer* renderer, int x, int y, int radius, SDL_Color color)
{
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_Rect dotRect = { x - radius, y - radius, 2 * radius, 2 * radius };
    SDL_RenderFillRect(renderer, &dotRect);
}

void calculateABTAS()
{
    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            if (maze[i][j] != 1)
            {
                ABTAS++;
            }
        }
    }
}


void randomItemPlacer(int total, int value, int* restrictedValues, int lengthOfresvalsarr)
{
    for (int z = 0; z < total; z++)
    {
        int a = randomInt(0, ABTAS);
        int b = 0;
        for (int i = 0; i < HEIGHT; i++)
        {
            for (int j = 0; j < WIDTH; j++)
            {
                int v = 1;
                for (int k = 0; k < lengthOfresvalsarr; k++)
                {
                    if (maze[i][j] == restrictedValues[k])
                    {
                        v = 0;
                    }
                }
                if (v)
                {
                    if (b == a)
                    {
                        maze[i][j] = value;
                        ABTAS--;
                        b = -1;
                        break;
                    }
                    else
                    {
                        b++;
                    }
                }
            }
            if (b == -1)
            {
                break;
            }
        }
    }
}

//points calculation

void calculatePoint()
{
    if (maze[pacmanY][pacmanX] == 2)
    {
        maze[pacmanY][pacmanX] = 0;
        points++;
    }
    else if (maze[pacmanY][pacmanX] == 3)
    {
        maze[pacmanY][pacmanX] = 0;
        points += 10;
    }
}

// rendering

void showPoint(SDL_Renderer* renderer, int score, int x, int y) {
    TTF_Font* textFont = TTF_OpenFont("C:/SDL2_libraries_/fontsttf/Roboto/Roboto-Regular.ttf", 16);
    SDL_Color fontColor = { 255,255,255,255 };
    char scoreText[20];
    snprintf(scoreText, sizeof(scoreText), "Score: %d", score);

    SDL_Surface* textSurface = TTF_RenderText_Solid(textFont, scoreText, fontColor);
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

    SDL_Rect textRect = { x,y,textSurface->w,textSurface->h };
    SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
}

void renderMaze(SDL_Renderer* renderer, SDL_Texture* cherryTexture)
{
    for (int row = 0; row < HEIGHT; row++)
    {
        for (int col = 0; col < WIDTH; col++)
        {
            SDL_Rect tile;
            tile.x = col * TILE_SIZE;
            tile.y = row * TILE_SIZE;
            tile.w = TILE_SIZE;
            tile.h = TILE_SIZE;

            if (maze[row][col] == 1)
            {
                SDL_SetRenderDrawColor(renderer, 0, 0, 139, 255); // Blue
                SDL_RenderFillRect(renderer, &tile);
            }
            else
            {
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Black
                SDL_RenderFillRect(renderer, &tile);
            }

            if (maze[row][col] == 3)
            {
                renderTexture(renderer, tile.x, tile.y, cherryTexture, 0);
            }
            else if (maze[row][col] == 2)
            {
                drawItem(renderer, tile.x + TILE_SIZE / 2, tile.y + TILE_SIZE / 2, SMALL_DOT_RADIUS, dotColor);
            }
        }
    }
}

void renderPacman(SDL_Renderer* renderer, SDL_Texture* pacmanOMTexture, SDL_Texture* pacmanCMTexture)
{
    SDL_Rect pacmanTile;
    pacmanTile.x = pacmanX * TILE_SIZE;
    pacmanTile.y = pacmanY * TILE_SIZE;
    int angle = 0;
    if (dx == 0 && dy == 0)
    {
        angle = 0;
    }
    else if (dx == 0)
    {
        angle = (dy == 1) ? 90 : 270;
    }
    else if (dy == 0)
    {
        angle = (dx == 1) ? 0 : 180;
    }
    if (timeCounter % 2 == 0)
    {
        renderTexture(renderer, pacmanTile.x, pacmanTile.y, pacmanOMTexture, angle);
    }
    else
    {
        renderTexture(renderer, pacmanTile.x, pacmanTile.y, pacmanCMTexture, angle);
    }
}

// pacmand movement

void updatePacmanPosition()
{
    if (speedCounter <= 0)
    {
        int newX = pacmanX + dx;
        int newY = pacmanY + dy;
        if (newX >= 0 && newX < WIDTH && newY >= 0 && newY < HEIGHT && maze[newY][newX] != 1)
        {
            pacmanX = newX;
            pacmanY = newY;
        }
        speedCounter = SPEED;
    }
    else
    {
        speedCounter--;
    }
}

void setDirection(int direction)
{
    switch (direction)
    {
    case 1:
        dx = 0;
        dy = -1;
        break; // Up
    case 2:
        dx = 0;
        dy = 1;
        break; // Down
    case 3:
        dx = -1;
        dy = 0;
        break; // Left
    case 4:
        dx = 1;
        dy = 0;
        break; // Right
    }
}
