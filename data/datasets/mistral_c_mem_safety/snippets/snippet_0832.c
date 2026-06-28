#include <stdio.h>

#define ARRAY_SIZE 10

void access_array(int index) {
    int array[ARRAY_SIZE] = {0};
    if (index < 0 || index >= ARRAY_SIZE) {
        printf("Index out of bounds\n");
        return;
    }
    printf("Array element: %d\n", array[index]);
}

int main() {
    access_array(5);
    return 0;
}