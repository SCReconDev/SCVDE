#include <stdio.h>
#include <stdlib.h>

void allocate_memory(int size) {
    int *array = (int *)malloc(size * sizeof(int));

    if (array == NULL) {
        printf("Memory allocation failed\n");
        return;
    }

    for (int i = 0; i < size; i++) {
        array[i] = i;
    }

    printf("Memory allocated and initialized\n");
    free(array);
}

int main() {
    int size;
    printf("Enter size: ");
    scanf("%d", &size);

    allocate_memory(size);

    return 0;
}