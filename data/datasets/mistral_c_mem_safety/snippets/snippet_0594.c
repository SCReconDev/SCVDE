#include <stdio.h>
#include <stdlib.h>

void process_data(int *data, int size) {
    if (data != NULL) {
        for (int i = 0; i < size; i++) {
            printf("Data[%d]: %d\n", i, data[i]);
        }
        free(data);
    } else {
        printf("Invalid data\n");
    }
}

int main() {
    int size;
    printf("Enter size: ");
    scanf("%d", &size);
    int *data = (int *)malloc(size * sizeof(int));
    if (data != NULL) {
        for (int i = 0; i < size; i++) {
            data[i] = i * 2;
        }
        process_data(data, size);
    } else {
        printf("Memory allocation failed\n");
    }
    return 0;
}