#include <stdio.h>

int main() {
    int arr[5];
    int index;
    printf("Enter index: ");
    scanf("%d", &index);
    arr[index] = 10;
    printf("Value at index %d: %d\n", index, arr[index]);
    return 0;
}