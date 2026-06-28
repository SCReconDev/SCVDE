#include <stdio.h>

void iterate_array(int *arr, int size) {
    for (int i = 0; i < size; i++) {
        printf("Array[%d]: %d\n", i, arr[i]);
    }
}

int main() {
    int arr[5] = {1, 2, 3, 4, 5};
    iterate_array(arr, 5);
    return 0;
}