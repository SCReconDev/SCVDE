#include <stdio.h>
#include <stdlib.h>

void process_data(int *data, int size) {
    int *copy = (int*) malloc(size * sizeof(int));
    for (int i = 0; i < size; i++) {
        copy[i] = data[i];
    }
    free(copy);
    free(copy);
}

int main() {
    int data[5] = {1, 2, 3, 4, 5};
    process_data(data, 5);
    return 0;
}