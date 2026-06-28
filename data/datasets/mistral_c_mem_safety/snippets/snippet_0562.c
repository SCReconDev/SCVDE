#include <stdio.h>

#define ARRAY_SIZE 10

int access_element(int index) {
    int array[ARRAY_SIZE] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    if (index >= 0 && index < ARRAY_SIZE) {
        return array[index];
    } else {
        printf("Index out of bounds.\n");
        return -1;
    }
}

int main() {
    int index;
    printf("Enter the index: ");
    scanf("%d", &index);
    int element = access_element(index);
    if (element != -1) {
        printf("Element at index %d: %d\n", index, element);
    }
    return 0;
}