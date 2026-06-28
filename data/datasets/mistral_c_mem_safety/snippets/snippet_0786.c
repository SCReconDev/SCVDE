#include <stdio.h>
#include <stdlib.h>

#define ARRAY_SIZE 10

void print_array(int *array) {
    for (int i = 0; i < ARRAY_SIZE; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

int main() {
    int array[ARRAY_SIZE];
    for (int i = 0; i < ARRAY_SIZE; i++) {
        array[i] = i;
    }
    print_array(array);
    return 0;
}