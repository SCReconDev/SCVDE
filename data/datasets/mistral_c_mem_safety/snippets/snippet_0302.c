#include <stdio.h>

int main() {
    int array[10];
    int index;
    printf("Enter index: ");
    scanf("%d", &index);
    printf("Value at index %d is %d\n", index, array[index]);
    return 0;
}