#include <stdio.h>

#define ARRAY_SIZE 10

void printElement(int index) {
    int array[ARRAY_SIZE] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    if (index < 0 || index >= ARRAY_SIZE) {
        printf("Index out of bounds.\n");
        return;
    }

    printf("Element at index %d: %d\n", index, array[index]);
}

int main() {
    int userIndex;
    printf("Enter index: ");
    scanf("%d", &userIndex);

    printElement(userIndex);

    return 0;
}