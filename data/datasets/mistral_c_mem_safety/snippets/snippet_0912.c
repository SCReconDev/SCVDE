#include <stdio.h>
#include <stdlib.h>

#define ARRAY_SIZE 10

void access_element(int *array, int index) {
    if (index < 0 || index >= ARRAY_SIZE) {
        fprintf(stderr, "Index out of bounds\n");
        return;
    }

    printf("Element at index %d: %d\n", index, array[index]);
}

int main() {
    int array[ARRAY_SIZE] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int index;

    printf("Enter index: ");
    scanf("%d", &index);

    access_element(array, index);

    return 0;
}