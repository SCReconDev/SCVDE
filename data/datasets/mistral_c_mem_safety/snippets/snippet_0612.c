#include <stdio.h>

#define ARRAY_SIZE 10

int safeCollectionAccess(int index) {
    int array[ARRAY_SIZE] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    if (index >= 0 && index < ARRAY_SIZE) {
        return array[index];
    } else {
        printf("Index out of bounds\n");
        return -1;
    }
}

int main() {
    int index = 5;
    int value = safeCollectionAccess(index);
    if (value != -1) {
        printf("Value at index %d: %d\n", index, value);
    }
    return 0;
}