#include <stdio.h>
#include <stdlib.h>

void process_data(int *data, int size) {
    for (int i = 0; i < size; i++) {
        printf("Data element: %d\n", data[i]);
    }

    free(data);
}

int main() {
    int size = 10;
    int *data = (int *)malloc(size * sizeof(int));

    if (data == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    for (int i = 0; i < size; i++) {
        data[i] = i;
    }

    process_data(data, size);

    return 0;
}