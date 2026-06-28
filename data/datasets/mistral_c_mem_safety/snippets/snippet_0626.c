#include <stdio.h>

#define ARRAY_SIZE 10

void iterate_array(int *array) {
    for (int i = 0; i < ARRAY_SIZE; i++) {
        printf("Array[%d]: %d\n", i, array[i]);
    }
}

int main() {
    int array[ARRAY_SIZE] = {0};
    for (int i = 0; i < ARRAY_SIZE; i++) {
        array[i] = i;
    }
    iterate_array(array);
    return 0;
}