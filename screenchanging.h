#pragma once
#ifndef SCREENCHANGING_H
#define SCREENCHANGING_H

extern int screenNumber;
extern int isHighScore;
extern int score;
extern int numberOfMaps;

int welcomescreen();
int mainGame(int mapNumber);
int selectMap();
int gameOver(int score_, int isHighScore_);
#endif