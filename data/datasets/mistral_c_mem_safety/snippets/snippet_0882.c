#include <stdio.h>
#include <stdlib.h>

#define ARRAY_SIZE 10

void access_array(int index) {
    int array[ARRAY_SIZE] = {0};

    if (index < 0 || index >= ARRAY_SIZE) {
        fprintf(stderr, "Index out of bounds\n");
        return;
    }

    printf("Array element at index %d: %d\n", index, array[index]);
}

int main() {
    int index;
    printf("Enter an index: ");
    scanf("%d", &index);

    access_array(index);
    return 0;
}