#include <stdio.h>
#include <stdlib.h>

void print_element(int* arr, int index) {
    printf("Element at index %d: %d\n", index, arr[index]);
}

int main() {
    int arr[5] = {1, 2, 3, 4, 5};
    int index;
    printf("Enter the index: ");
    scanf("%d", &index);
    print_element(arr, index);
    return 0;
}