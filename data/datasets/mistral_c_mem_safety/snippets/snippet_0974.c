#include <stdio.h>
#include <stdlib.h>

void process_data(int *data, int size) {
    int *copy = (int *)malloc(size * sizeof(int));
    if (copy == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return;
    }
    for (int i = 0; i < size; i++) {
        copy[i] = data[i];
    }
    printf("Data processed\n");
    free(copy);
}

int main() {
    int data[] = {1, 2, 3, 4, 5};
    int size = sizeof(data) / sizeof(data[0]);
    process_data(data, size);
    return 0;
}