#include <stdio.h>

#define ARRAY_SIZE 10

void printArray(int arr[]) {
    for (int i = 0; i < ARRAY_SIZE; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int arr[ARRAY_SIZE] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    printArray(arr);
    return 0;
}