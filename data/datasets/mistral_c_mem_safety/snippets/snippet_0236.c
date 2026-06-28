#include <stdio.h>

void print_array(int *array, int size) {
    for (int i = 0; i <= size; i++) {
        printf("Element: %d\n", array[i]);
    }
}

int main() {
    int numbers[5] = {1, 2, 3, 4, 5};
    print_array(numbers, 5);
    return 0;
}