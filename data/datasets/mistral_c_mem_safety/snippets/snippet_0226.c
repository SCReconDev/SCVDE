#include <stdio.h>

int main() {
    int array[5] = {1, 2, 3, 4, 5};
    for (int i = 0; i <= 5; i++) {
        printf("Value at index %d: %d\n", i, array[i]);
    }
    return 0;
}