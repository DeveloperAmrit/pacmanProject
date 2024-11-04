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

void reverseArrayRowWise(int* array, int rows, int cols) {
    for (int i = 0; i < rows / 2; i++) {
        for (int j = 0; j < cols; j++) {

            // Calculate indices for elements to swap
            int index1 = i * cols + j;
            int index2 = (rows - i - 1) * cols + j;

            // Swap elements
            int temp = array[index1];
            array[index1] = array[index2];
            array[index2] = temp;
        }
    }
}

double distanceBetweenTwoPoints(int x1, int y1, int x2, int y2) {
    int a = pow((x2 - x1), 2) + pow((y2 - y1), 2);
    return pow(a, 0.5);
}