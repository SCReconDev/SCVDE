#include <stdio.h>
#include <stdlib.h>

void access_element(int *array, int index) {
    printf("Element at index %d: %d\n", index, array[index]);
}

int main() {
    int array[5] = {1, 2, 3, 4, 5};
    int index = 7;
    access_element(array, index);
    return 0;
}