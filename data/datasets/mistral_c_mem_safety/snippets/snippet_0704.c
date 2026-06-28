#include <stdio.h>
#include <stdlib.h>

void processData(int *data, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", data[i]);
    }
    printf("\n");
    free(data);
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
        data[i] = i;
    }
    processData(data, size);
    return 0;
}