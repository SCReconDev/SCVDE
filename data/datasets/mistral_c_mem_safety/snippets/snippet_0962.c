#include <stdio.h>

#define ARRAY_SIZE 10

void access_element(int index) {
    int array[ARRAY_SIZE] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    if (index < 0 || index >= ARRAY_SIZE) {
        printf("Index out of bounds\n");
        return;
    }

    printf("Element at index %d: %d\n", index, array[index]);
}

int main() {
    access_element(5);
    return 0;
}