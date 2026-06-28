#include <stdio.h>
#include <stdlib.h>

#define ARRAY_SIZE 10

void access_array_element(int index) {
    int array[ARRAY_SIZE] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    if (index < 0 || index >= ARRAY_SIZE) {
        fprintf(stderr, "Index out of bounds\n");
        exit(EXIT_FAILURE);
    }

    printf("Array element at index %d is %d\n", index, array[index]);
}

int main() {
    int index;

    printf("Enter an index: ");
    scanf("%d", &index);

    access_array_element(index);

    return 0;
}