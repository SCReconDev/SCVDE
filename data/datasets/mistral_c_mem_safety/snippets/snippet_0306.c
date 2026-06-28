#include <stdio.h>

int main() {
    int array[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    for (int i = 0; i <= 10; i++) {
        printf("Value at index %d is %d\n", i, array[i]);
    }
    return 0;
}