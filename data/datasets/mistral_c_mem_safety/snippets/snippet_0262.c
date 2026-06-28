#include <stdio.h>
#include <stdlib.h>

int main() {
    int *array = (int *)malloc(5 * sizeof(int));
    int index = 6;
    array[index] = 10;
    free(array);
    return 0;
}