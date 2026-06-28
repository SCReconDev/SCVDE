#include <stdio.h>

#define ARRAY_SIZE 10

void print_element(int index) {
    int array[ARRAY_SIZE] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    if (index >= 0 && index < ARRAY_SIZE) {
        printf("Element at index %d: %d\n", index, array[index]);
    } else {
        printf("Index out of bounds\n");
    }
}

int main() {
    int index;
    printf("Enter the index: ");
    scanf("%d", &index);
    print_element(index);
    return 0;
}