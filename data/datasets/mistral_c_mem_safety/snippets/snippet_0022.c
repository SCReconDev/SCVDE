#include <stdio.h>
#include <stdlib.h>

void printElement(int* array, int index) {
    printf("Element at index %d: %d\n", index, array[index]);
}

int main() {
    int* numbers = (int*)malloc(5 * sizeof(int));
    for (int i = 0; i < 5; i++) {
        numbers[i] = i * 10;
    }

    int userIndex;
    printf("Enter the index to print: ");
    scanf("%d", &userIndex);
    printElement(numbers, userIndex);

    free(numbers);
    return 0;
}