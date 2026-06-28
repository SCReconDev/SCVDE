#include <stdio.h>
#include <stdlib.h>

#define ARRAY_SIZE 10

void access_array(int* array, int index) {
    if (index < 0 || index >= ARRAY_SIZE) {
        fprintf(stderr, "Index out of bounds\n");
        return;
    }
    printf("Array element at index %d: %d\n", index, array[index]);
}

int main() {
    int array[ARRAY_SIZE] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    access_array(array, 5);
    return 0;
}