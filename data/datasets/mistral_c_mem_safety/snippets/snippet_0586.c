#include <stdio.h>

void iterate_collection(int* collection, size_t size) {
    for (size_t i = 0; i < size; ++i) {
        printf("Value at index %zu: %d\n", i, collection[i]);
    }
}

int main() {
    int collection[] = {1, 2, 3, 4, 5};
    size_t size = sizeof(collection) / sizeof(collection[0]);
    iterate_collection(collection, size);
    return 0;
}