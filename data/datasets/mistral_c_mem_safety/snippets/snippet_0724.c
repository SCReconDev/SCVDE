#include <stdio.h>
#include <stdlib.h>

void process_data(int *data, int size) {
    if (data == NULL || size <= 0) {
        printf("Invalid data or size\n");
        return;
    }
    for (int i = 0; i < size; i++) {
        printf("%d ", data[i]);
    }
    printf("\n");
    free(data);
}

int main() {
    int size = 10;
    int *data = (int*)malloc(size * sizeof(int));
    if (data != NULL) {
        for (int i = 0; i < size; i++) {
            data[i] = i;
        }
        process_data(data, size);
    } else {
        printf("Memory allocation failed\n");
    }
    return 0;
}