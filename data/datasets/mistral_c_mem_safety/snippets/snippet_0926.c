#include <stdio.h>

#define ARRAY_SIZE 10

void print_array(int array[ARRAY_SIZE]) {
    for (int i = 0; i < ARRAY_SIZE; i++) {
        printf("Array[%d]: %d\n", i, array[i]);
    }
}

int main() {
    int array[ARRAY_SIZE] = {0};
    for (int i = 0; i < ARRAY_SIZE; i++) {
        array[i] = i;
    }
    print_array(array);
    return 0;
}