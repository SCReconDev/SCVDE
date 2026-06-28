#include <stdio.h>

void access_element(int *array, int index, int size) {
    if (index >= 0 && index < size) {
        printf("Element at index %d: %d\n", index, array[index]);
    } else {
        printf("Index out of bounds\n");
    }
}

int main() {
    int array[] = {1, 2, 3, 4, 5};
    int size = sizeof(array) / sizeof(array[0]);
    access_element(array, 2, size);
    return 0;
}