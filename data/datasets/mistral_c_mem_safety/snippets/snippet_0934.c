#include <stdio.h>
#include <stdlib.h>

void process_data(int* data, size_t size) {
    for (size_t i = 0; i < size; i++) {
        printf("Data element %zu: %d\n", i, data[i]);
    }
}

int main() {
    size_t size;
    printf("Enter size: ");
    scanf("%zu", &size);

    int* data = (int*)malloc(size * sizeof(int));

    if (data == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    for (size_t i = 0; i < size; i++) {
        data[i] = i;
    }

    process_data(data, size);

    free(data);

    return 0;
}