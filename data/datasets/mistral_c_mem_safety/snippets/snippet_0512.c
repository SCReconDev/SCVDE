#include <stdio.h>

int access_element(int* array, size_t index, size_t size) {
    if (index < size) {
        return array[index];
    } else {
        printf("Index out of bounds\n");
        return -1;
    }
}

int main() {
    int array[] = {1, 2, 3, 4, 5};
    size_t size = sizeof(array) / sizeof(array[0]);
    int element = access_element(array, 2, size);
    if (element != -1) {
        printf("Element: %d\n", element);
    }
    return 0;
}