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

int ghostsX[6];
int ghostsY[6];
int gdxarr[6];
int gdyarr[6];
int ghostSpeedCounterarr[6];

int isHighScore = 0;

// generalised functions

void renderTexture(SDL_Renderer* renderer, int x, int y, SDL_Texture* Texture, int angle, int TILE_SIZE)
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

void calculateABTAS(int HEIGHT, int WIDTH, int** maze, int* ABTAS)
{
    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            if (maze[i][j] != 1)
            {
                *ABTAS += 1;
            }
        }
    }
}


void randomItemPlacer(int total, int value, int* restrictedValues, int lengthOfresvalsarr, int* ABTAS, int HEIGHT, int WIDTH, int** maze)
{
    for (int z = 0; z < total; z++)
    {
        int a = randomInt(0, *ABTAS);
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
                        *ABTAS-=1;
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

int getDirection(int dx, int dy) {
    if (dx == 0 && dy == 0) {
        return 4;
    }
    else if (dx == 0) {
        return (dy == 1) ? 2 : 1;
    }
    else if (dy == 0) {
        return (dx == 1) ? 4 : 3;
    }
    return 4;
}

int getOppositeDirection(int direction) {
    switch (direction) {
    case 1:
        return 2;
        break;
    case 2:
        return 1;
        break;
    case 3:
        return 4;
        break;
    case 4:
        return 3;
        break;
    }
    return 4;
}

//points calculation

void calculatePoint(int** maze, int WIDTH, int pacmanX, int pacmanY, int* points)
{
    if (maze[pacmanY][pacmanX] == 2)
    {
        maze[pacmanY][pacmanX] = 0;
        *points+=1;
    }
    else if (maze[pacmanY][pacmanX] == 3)
    {
        maze[pacmanY][pacmanX] = 0;
        *points += 10;
    }
}

// rendering

void showPoint(SDL_Renderer* renderer, int score, int x, int y) {
    TTF_Font* textFont = TTF_OpenFont("Roboto-Regular.ttf", 16);
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

void renderMaze(SDL_Renderer* renderer, SDL_Texture* cherryTexture, int TILE_SIZE, int WIDTH, int HEIGHT, int** maze, int SMALL_DOT_RADIUS, SDL_Color dotColor)
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
                renderTexture(renderer, tile.x, tile.y, cherryTexture, 0, TILE_SIZE);
            }
            else if (maze[row][col] == 2)
            {
                drawItem(renderer, tile.x + TILE_SIZE / 2, tile.y + TILE_SIZE / 2, SMALL_DOT_RADIUS, dotColor);
            }
        }
    }
}

void renderPacman(SDL_Renderer* renderer, SDL_Texture* pacmanOMTexture, SDL_Texture* pacmanCMTexture, int TILE_SIZE, int pacmanX, int pacmanY, int dx, int dy, int timeCounter)
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
        renderTexture(renderer, pacmanTile.x, pacmanTile.y, pacmanOMTexture, angle, TILE_SIZE);
    }
    else
    {
        renderTexture(renderer, pacmanTile.x, pacmanTile.y, pacmanCMTexture, angle, TILE_SIZE);
    }
}


void renderGhosts(SDL_Renderer* renderer, SDL_Texture** arrayOfTextures, int total, int TILE_SIZE, int NUMOFGHOSTS) {
    for (int i = 0;i < NUMOFGHOSTS;i++) {
        renderTexture(renderer, ghostsX[i] * TILE_SIZE, ghostsY[i] * TILE_SIZE, arrayOfTextures[i], 0, TILE_SIZE);
    }
}

// pacmand movement

void updatePacmanPosition(int HEIGHT, int WIDTH, int** maze, int SPEED, int* speedCounter, int* pacmanX, int* pacmanY, int dx, int dy)
{
    if (*speedCounter <= 0)
    {
        int newX = *pacmanX + dx;
        int newY = *pacmanY + dy;
        if (newX >= 0 && newX < WIDTH && newY >= 0 && newY < HEIGHT && maze[newY][newX] != 1)
        {
            *pacmanX = newX;
            *pacmanY = newY;
        }
        *speedCounter = SPEED;
    }
    else
    {
        *speedCounter-=1;
    }
}

void setDirection(int direction, int* dx_, int* dy_)
{
    switch (direction)
    {
    case 1:
        *dx_ = 0;
        *dy_ = -1;
        break; // Up
    case 2:
        *dx_ = 0;
        *dy_ = 1;
        break; // Down
    case 3:
        *dx_ = -1;
        *dy_ = 0;
        break; // Left
    case 4:
        *dx_ = 1;
        *dy_ = 0;
        break; // Right
    }
}

// ghosts movement

void moveGhostRandomly(int* gx, int* gy, int* gdx, int* gdy, int* ghostSpeedCounter, int ghostSpeed, int HEIGHT, int WIDTH, int** maze) {
    if (*ghostSpeedCounter == ghostSpeed) {
        int tgdx = 1;
        int tgdy = 0;
        int allDirections[4] = { 1,2,3,4 };
        int validDirections[4] = { 1,2,3,4 }, nvalid = 0;

        for (int i = 0;i < 4;i++) {
            setDirection(allDirections[i], &tgdx, &tgdy);
            if ((0 <= *gy + tgdy) && (*gy + tgdy < HEIGHT) && (0 <= *gx + tgdx) && (*gx + tgdx < WIDTH)) {
                if (maze[*gy + tgdy][*gx + tgdx] != 1) {
                    nvalid++;
                }
            }
        }
        if (nvalid > 1) {
            nvalid = 0;
            for (int i = 0;i < 4;i++) {
                setDirection(allDirections[i], &tgdx, &tgdy);
                if ((*gdy != 0 && tgdy != -*gdy) || (*gdx != 0 && tgdx != -*gdx)) {       // this condition is rejecting backward movement
                    if ((0 <= *gy + tgdy) && (*gy + tgdy < HEIGHT) && (0 <= *gx + tgdx) && (*gx + tgdx < WIDTH)) {
                        if (maze[*gy + tgdy][*gx + tgdx] != 1) {
                            validDirections[nvalid] = allDirections[i];
                            nvalid++;
                        }
                    }
                    //printf("\nAAYA nvalid = %d",nvalid);
                }
            }
            if (nvalid != 0) {
                int rand_i = randomInt(0, nvalid - 1);
                setDirection(validDirections[rand_i], gdx, gdy);
                //printf("\t(%d + %d,  %d + %d)", *gx, *gdx, *gy, *gdy);
            }
        }
        else {
            //printf("\nONE WAY");
            *gdx = -*gdx;
            *gdy = -*gdy;
        }
        *gx = *gx + *gdx;
        *gy = *gy + *gdy;
        *ghostSpeedCounter = 0;
    }
    else {
        *ghostSpeedCounter = *ghostSpeedCounter + 1;
    }

}

// implementing BFS for chasing pacman

#define VAMR  1000
#define EQAMR 1000


void explore(int node[2], int visited[(int)VAMR][2], int* Vn, int expoqueue[(int)EQAMR][2], int* En, int HEIGHT, int WIDTH, int** maze) {

    int ix = node[0];
    int iy = node[1];

    int allDirections[4] = { 1,2,3,4 };
    int tdx = 1;
    int tdy = 0;

    //printf("\nAround (%d,%d) we have", ix, iy);

    for (int i = 0;i < 4;i++) {
        setDirection(allDirections[i], &tdx, &tdy);
        if ((0 <= iy + tdy) && (iy + tdy < HEIGHT) && (0 <= ix + tdx) && (ix + tdx < WIDTH)) {
            if (maze[iy + tdy][ix + tdx] != 1) {
                int alreadyAvInEQ = 0;
                int alreadyAvInV = 0;
                for (int i = 0;i < *En;i++) {
                    if (expoqueue[i][0] == node[0] + tdx && expoqueue[i][1] == node[1] + tdy) {
                        alreadyAvInEQ = 1;
                    }
                }
                for (int i = 0;i < *Vn;i++) {
                    if (visited[i][0] == node[0] + tdx && visited[i][1] == node[1] + tdy) {
                        alreadyAvInV = 1;
                    }
                }
                if (alreadyAvInV == 0) {
                    visited[*Vn][0] = node[0] + tdx;
                    visited[*Vn][1] = node[1] + tdy;
                    *Vn += 1;
                }
                if (alreadyAvInEQ == 0) {
                    expoqueue[*En][0] = node[0] + tdx;
                    expoqueue[*En][1] = node[1] + tdy;
                    *En += 1;
                    //printf("\t(%d,%d)", ix + tdx, iy + tdy);
                }
            }
        }
    }
}

int findParentOf(int node[2], int visited[(int)VAMR][2], int Vn, int parentNode[2]) {
    int tdx = 1;
    int tdy = 0;
    int allDirections[4] = { 1,2,3,4 };

    int x = node[0];
    int y = node[1];

    int index = 0;
    for (int i = 0;i < Vn;i++) {
        if (visited[i][0] == x && visited[i][1] == y) {
            index = i;
            break;
        }
    }
    for (int i = 0;i < 4;i++) {
        setDirection(allDirections[i], &tdx, &tdy);
        for (int j = 0;j < index;j++) {
            if (visited[j][0] == x + tdx && visited[j][1] == y + tdy) {
                parentNode[0] = x + tdx;
                parentNode[1] = y + tdy;
                return 0;
            }
        }
    }
}

void findFinalPath(int pacmanX_, int pacmanY_, int* ghostX, int* ghostY, int visited[VAMR][2], int Vn, int finalPath[VAMR][2], int* FPn) {

    int path[(int)VAMR][2];
    int Pn = 0;

    for (int i = 1;i < Vn;i++) {
        int node[2] = { visited[i][0], visited[i][1] };
        int pnode[2] = { 0,0 };
        findParentOf(node, visited, Vn, pnode);
        //printf("\nParent of (%d,%d) is (%d,%d)", node[0], node[1], pnode[0], pnode[1]);

        int isAlreadyP = 0;
        for (int j = 0;j < Pn;j++) {
            if (path[j][0] == pnode[0] && path[j][1] == pnode[1]) {
                isAlreadyP = 1;
            }
        }
        if (!isAlreadyP) {
            path[Pn][0] = pnode[0];
            path[Pn][1] = pnode[1];
            Pn++;
        }

    }
    path[Pn][0] = pacmanX_;
    path[Pn][1] = pacmanY_;
    Pn++;
    /*printf("\nPath = ");
    for (int i = 0;i < Pn;i++) {
        printf("(%d,%d),", path[i][0], path[i][1]);
    }*/

    // 4 nov

    int tempX = path[Pn - 1][0];
    int tempY = path[Pn - 1][1];
    finalPath[0][0] = tempX;
    finalPath[0][1] = tempY;
    *FPn += 1;
    int a = Pn - 1;
    while (1) {
        for (int i = a;i >= 0;i--) {
            if (abs(tempX - path[i][0]) + abs(tempY - path[i][1]) == 1) {
                tempX = path[i][0];
                tempY = path[i][1];
                if (tempX == *ghostX && tempY == *ghostY) {
                    break;
                }
                finalPath[*FPn][0] = tempX;
                finalPath[*FPn][1] = tempY;
                *FPn += 1;
                a = i;
                break;
            }
        }
        if (tempX == *ghostX && tempY == *ghostY) {
            break;
        }
    }
    reverseArrayRowWise(finalPath, *FPn, 2);
    /* printf("\nFinalPath = ");
     for (int i = 0;i < *FPn;i++) {
         printf("(%d,%d),", finalPath[i][0], finalPath[i][1]);
     }*/

}

void applyBFS(int pacmanX_, int pacmanY_, int* ghostX, int* ghostY, int** maze, int finalPath[VAMR][2], int* FPn, int HEIGHT, int WIDTH) {

    int visited[(int)VAMR][2];
    long int Vn = 0;
    int expoq[(int)EQAMR][2];
    long int En = 0;

    expoq[En][0] = *ghostX;
    expoq[En][1] = *ghostY;
    En += 1;

    visited[Vn][0] = *ghostX;
    visited[Vn][1] = *ghostY;
    Vn += 1;

    for (int i = 0;i < En;i++) {
        if (En >= EQAMR || Vn >= VAMR) {
            //printf("limit reached En=%d Vn=%d", En, Vn);
            break;
        }
        explore(expoq[i], visited, &Vn, expoq, &En, HEIGHT, WIDTH, maze);
        if (expoq[i][0] == pacmanX_ && expoq[i][1] == pacmanY_) {
            //printf("\t GOT IT (%d,%d)", expoq[i][0], expoq[i][1]);

            findFinalPath(pacmanX_, pacmanY_, ghostX, ghostY, visited, Vn, finalPath, FPn);
            break;
        }

    }
}

void chasePacman(int pacmanX_, int pacmanY_, int* ghostX, int* ghostY, int** maze, int* speedCounter, int ghostSpeed, int HEIGHT, int WIDTH) {
    if (*speedCounter == ghostSpeed) {
        int finalPath[VAMR][2];
        int FPn = 0;
        applyBFS(pacmanX_, pacmanY_, ghostX, ghostY, maze, finalPath, &FPn, HEIGHT, WIDTH);
        *ghostX = finalPath[0][0];
        *ghostY = finalPath[0][1];
        //printf("\nchasePacman chala");
        *speedCounter = 0;
    }
    else {
        *speedCounter += 1;
    }


}

// ghost movement control


void ghostMovement(int NUMOFGHOSTS, int maxdistacnetochase, int pacmanX, int pacmanY, int ghostSpeed, int HEIGHT, int WIDTH, int** maze) {
    for (int i = 0;i < NUMOFGHOSTS;i++) {
        if (distanceBetweenTwoPoints(pacmanX, pacmanY, ghostsX[i], ghostsY[i]) > maxdistacnetochase) {
            moveGhostRandomly(&ghostsX[i], &ghostsY[i], &gdxarr[i], &gdyarr[i], &ghostSpeedCounterarr[i], ghostSpeed, HEIGHT, WIDTH, maze);
        }
        else {
            chasePacman(pacmanX, pacmanY, &ghostsX[i], &ghostsY[i], maze, &ghostSpeedCounterarr[i], ghostSpeed, HEIGHT, WIDTH);
        }
    }
    //printf("%d", maxdistacnetochase);
}


// collision 

int isCollided(int NUMOFGHOSTS, int pacmanX, int pacmanY, int points) {
    for (int i = 0;i < NUMOFGHOSTS;i++) {
        if (ghostsX[i] == pacmanX && ghostsY[i] == pacmanY) {
            printf("\n%d", points);
            printf("\nGAME OVER");
            screenNumber = -1;
            return 1;
        }
    }
    return 0;
}



