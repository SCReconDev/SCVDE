#include <stdio.h>
#include <stdlib.h>

#define ARRAY_SIZE 10

void access_array(int* arr, int index) {
    if (index < 0 || index >= ARRAY_SIZE) {
        fprintf(stderr, "Index out of bounds\n");
        return;
    }

    printf("Array element at index %d: %d\n", index, arr[index]);
}

int main() {
    int arr[ARRAY_SIZE] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int index;

    printf("Enter index: ");
    scanf("%d", &index);

    access_array(arr, index);

    return 0;
}