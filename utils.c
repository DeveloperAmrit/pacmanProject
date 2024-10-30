#include <stdlib.h>
#include <time.h>

int randomInt(int min, int max) {
    return min + rand() % (max - min + 1);
}
