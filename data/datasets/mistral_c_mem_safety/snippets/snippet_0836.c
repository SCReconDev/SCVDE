#include <stdio.h>

#define ARRAY_SIZE 10

void iterate_array() {
    int array[ARRAY_SIZE] = {0};
    for (int i = 0; i < ARRAY_SIZE; i++) {
        printf("Array element: %d\n", array[i]);
    }
}

int main() {
    iterate_array();
    return 0;
}