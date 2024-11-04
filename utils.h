#pragma once
#ifndef UTILS_H
#define UTILS_H

int randomInt(int min, int max);
int GIF(double x);
int copyArray(int* destination, int* source,int length);
void reverseArrayRowWise(int* array, int rows, int cols);
double distanceBetweenTwoPoints(int x1, int y1, int x2, int y2);
#endif