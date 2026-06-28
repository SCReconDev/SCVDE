#include <stdio.h>

#define ARRAY_SIZE 10

void print_array(int arr[]) {
    for (int i = 0; i <= ARRAY_SIZE; i++) {
        printf("Element at index %d: %d\n", i, arr[i]);
    }
}

int main() {
    int arr[ARRAY_SIZE] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    print_array(arr);

    return 0;
}