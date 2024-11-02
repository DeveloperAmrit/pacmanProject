#pragma once
// mazes.h
#ifndef MAZES_H
#define MAZES_H


#define WIDTH1 10
#define HEIGHT1 10
#define MAZE1_START_X 7
#define MAZE1_START_Y 8
#define MAZE1_N_GHOSTS 2
extern int maze1ghostsX[MAZE1_N_GHOSTS];
extern int maze1ghostsY[MAZE1_N_GHOSTS];
extern int maze1[HEIGHT1][WIDTH1];

#define WIDTH2 12
#define HEIGHT2 8
#define MAZE2_START_X 4
#define MAZE2_START_Y 6
#define MAZE2_N_GHOSTS 3
extern int maze2ghostsX[MAZE2_N_GHOSTS];
extern int maze2ghostsY[MAZE2_N_GHOSTS];
extern int maze2[HEIGHT2][WIDTH2];

#define WIDTH3 15
#define HEIGHT3 13
#define MAZE3_START_X 6
#define MAZE3_START_Y 8
#define MAZE3_N_GHOSTS 3
extern int maze3ghostsX[MAZE3_N_GHOSTS];
extern int maze3ghostsY[MAZE3_N_GHOSTS];
extern int maze3[HEIGHT3][WIDTH3];

#define WIDTH4 20
#define HEIGHT4 15
#define MAZE4_START_X 12
#define MAZE4_START_Y 10
#define MAZE4_N_GHOSTS 4
extern int maze4ghostsX[MAZE4_N_GHOSTS];
extern int maze4ghostsY[MAZE4_N_GHOSTS];
extern int maze4[HEIGHT4][WIDTH4];

#define WIDTH5 25
#define HEIGHT5 20
#define MAZE5_START_X 11
#define MAZE5_START_Y 10
#define MAZE5_N_GHOSTS 5
extern int maze5ghostsX[MAZE5_N_GHOSTS];
extern int maze5ghostsY[MAZE5_N_GHOSTS];
extern int maze5[HEIGHT5][WIDTH5];

#define WIDTH6 28
#define HEIGHT6 32
#define MAZE6_START_X 1
#define MAZE6_START_Y 1
#define MAZE6_N_GHOSTS 6
extern int maze6ghostsX[MAZE6_N_GHOSTS];
extern int maze6ghostsY[MAZE6_N_GHOSTS];
extern int maze6[HEIGHT6][WIDTH6];


#endif  // MAZES_H