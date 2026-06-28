#include <stdio.h>

#define ARRAY_SIZE 10

void print_element(int arr[], int index) {
    if (index < 0 || index >= ARRAY_SIZE) {
        printf("Index out of bounds\n");
        return;
    }

    printf("Element at index %d: %d\n", index, arr[index]);
}

int main() {
    int arr[ARRAY_SIZE] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int index;

    printf("Enter index: ");
    scanf("%d", &index);

    print_element(arr, index);

    return 0;
}