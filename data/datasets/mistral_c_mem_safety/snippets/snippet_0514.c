#include <stdio.h>
#include <stdlib.h>

void process_data(int* data, size_t size) {
    for (size_t i = 0; i < size; i++) {
        printf("Data[%zu]: %d\n", i, data[i]);
    }
}

int main() {
    size_t size = 5;
    int* data = (int*)malloc(size * sizeof(int));
    if (data != NULL) {
        for (size_t i = 0; i < size; i++) {
            data[i] = i * 2;
        }
        process_data(data, size);
        free(data);
    }
    return 0;
}