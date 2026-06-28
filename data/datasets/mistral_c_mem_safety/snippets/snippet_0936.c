#include <stdio.h>

void print_array(int* arr, size_t size) {
    for (size_t i = 0; i < size; i++) {
        printf("Array element %zu: %d\n", i, arr[i]);
    }
}

int main() {
    int arr[5] = {0, 1, 2, 3, 4};
    size_t size = sizeof(arr) / sizeof(arr[0]);

    print_array(arr, size);

    return 0;
}