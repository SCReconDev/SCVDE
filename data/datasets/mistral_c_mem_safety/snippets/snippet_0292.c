#include <stdio.h>

void print_element(int *array, int index) {
    printf("Element at index %d: %d\n", index, array[index]);
}

int main() {
    int numbers[5] = {1, 2, 3, 4, 5};
    int index = 7;
    print_element(numbers, index);
    return 0;
}