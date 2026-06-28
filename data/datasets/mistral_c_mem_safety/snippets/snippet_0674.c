#include <stdio.h>
#include <stdlib.h>

void process_data(int *data, int size) {
    for (int i = 0; i < size; i++) {
        printf("Data[%d]: %d\n", i, data[i]);
    }
}

int main() {
    int size;
    printf("Enter size: ");
    scanf("%d", &size);

    int *data = (int *)malloc(size * sizeof(int));

    if (data == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    for (int i = 0; i < size; i++) {
        data[i] = i * 2;
    }

    process_data(data, size);

    free(data);

    return 0;
}