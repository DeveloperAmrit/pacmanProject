#include <stdlib.h>
#include <time.h>
#include <math.h>

int randomInt(int min, int max) {
    return min + rand() % (max - min + 1);
}

int GIF(double x) {
    return (int)floor(x);
}