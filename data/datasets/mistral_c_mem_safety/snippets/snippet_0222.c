#include <stdio.h>

int main() {
    int array[5] = {1, 2, 3, 4, 5};
    int index;
    printf("Enter index: ");
    scanf("%d", &index);
    printf("Value at index %d: %d\n", index, array[index]);
    return 0;
}