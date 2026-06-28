#include <stdio.h>
#include <stdlib.h>

int *create_array(int size) {
    int *arr = (int *)malloc(size * sizeof(int));
    if (arr == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    return arr;
}

int main() {
    int *arr = create_array(10);
    for (int i = 0; i < 10; i++) {
        arr[i] = i;
    }
    return 0;
}