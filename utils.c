#include <stdlib.h>
#include <time.h>
#include <math.h>

int randomInt(int min, int max) {
    if (min == max+1) {
        return min;
    }
    return min + rand() % (max - min + 1);
}

int GIF(double x) {
    return (int)floor(x);
}

int copyArray(int* destination, int* source,int length) {
    for (int i = 0;i < length;i++) {
        destination[i] = source[i];
    }
    return 0;
}