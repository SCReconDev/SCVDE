#include <stdio.h>

#define MAX_SIZE 10

void printElement(int arr[], int index) {
    if (index >= 0 && index < MAX_SIZE) {
        printf("Element at index %d: %d\n", index, arr[index]);
    } else {
        printf("Index out of bounds.\n");
    }
}

int main() {
    int arr[MAX_SIZE] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int index;
    printf("Enter index: ");
    scanf("%d", &index);
    printElement(arr, index);
    return 0;
}