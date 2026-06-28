#include <stdio.h>
#include <stdlib.h>

#define ARRAY_SIZE 10

void access_element(int index) {
    int array[ARRAY_SIZE] = {0};
    if (index >= 0 && index < ARRAY_SIZE) {
        printf("Element at index %d is %d\n", index, array[index]);
    } else {
        printf("Index out of bounds.\n");
    }
}

int main() {
    int index;
    printf("Enter index: ");
    scanf("%d", &index);
    access_element(index);
    return 0;
}