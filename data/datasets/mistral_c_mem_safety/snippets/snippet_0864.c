#include <stdio.h>
#include <stdlib.h>

void process_data(int *data, size_t size) {
    int *copy = (int*)malloc(size * sizeof(int));

    if (copy == NULL) {
        printf("Memory allocation failed\n");
        return;
    }

    for (size_t i = 0; i < size; i++) {
        copy[i] = data[i];
    }

    printf("Data processed\n");

    free(copy);
}

int main() {
    int data[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    size_t size = sizeof(data) / sizeof(data[0]);
    process_data(data, size);
    return 0;
}