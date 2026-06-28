#include <stdio.h>
#include <stdlib.h>

void process_data(int* data, size_t size) {
    int* copy = malloc(size * sizeof(int));
    if (copy != NULL) {
        memcpy(copy, data, size * sizeof(int));
        printf("Data processed\n");
        free(copy);
    } else {
        printf("Memory allocation failed\n");
    }
}

int main() {
    int data[] = {1, 2, 3, 4, 5};
    size_t size = sizeof(data) / sizeof(data[0]);
    process_data(data, size);
    return 0;
}