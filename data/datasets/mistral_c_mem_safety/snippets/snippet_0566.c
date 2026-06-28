#include <stdio.h>

void print_array(int* array, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

int main() {
    int array[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int size = sizeof(array) / sizeof(array[0]);
    print_array(array, size);
    return 0;
}