#include <stdio.h>
#include <stdlib.h>

int *create_array(int size) {
    int *array = (int *)malloc(size * sizeof(int));
    for (int i = 0; i < size; i++) {
        array[i] = i;
    }
    return array;
}

int main() {
    int *numbers = create_array(5);
    for (int i = 0; i < 5; i++) {
        printf("Numbers[%d]: %d\n", i, numbers[i]);
    }
    return 0;
}