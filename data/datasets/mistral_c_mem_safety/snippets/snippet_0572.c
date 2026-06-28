#include <stdio.h>

void access_element(int* array, size_t index, size_t array_size) {
    if (index < array_size) {
        printf("Element at index %zu: %d\n", index, array[index]);
    } else {
        printf("Index out of bounds\n");
    }
}

int main() {
    int array[] = {1, 2, 3, 4, 5};
    size_t array_size = sizeof(array) / sizeof(array[0]);
    access_element(array, 2, array_size);
    return 0;
}