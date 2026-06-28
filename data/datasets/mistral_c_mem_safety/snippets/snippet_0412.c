#include <stdio.h>

int main() {
    int arr[5] = {1, 2, 3, 4, 5};
    int index;
    printf("Enter index: ");
    scanf("%d", &index);
    printf("Value at index %d is %d\n", index, arr[index]);
    return 0;
}