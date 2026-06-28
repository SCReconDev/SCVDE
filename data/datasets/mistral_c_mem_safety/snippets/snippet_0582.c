#include <stdio.h>

void access_collection(int* collection, size_t size, size_t index) {
    if (index < size) {
        printf("Value at index %zu: %d\n", index, collection[index]);
    } else {
        printf("Index out of bounds\n");
    }
}

int main() {
    int collection[] = {1, 2, 3, 4, 5};
    size_t size = sizeof(collection) / sizeof(collection[0]);
    access_collection(collection, size, 2);
    return 0;
}