#include <stdio.h>

void print_element(int arr[], int index) {
    printf("Element at index %d is %d\n", index, arr[index]);
}

int main() {
    int arr[5] = {1, 2, 3, 4, 5};
    int index;
    printf("Enter index: ");
    scanf("%d", &index);
    print_element(arr, index);
    return 0;
}