#include <stdio.h>
#include <stdlib.h>

int main() {
    int *array = (int *)malloc(10 * sizeof(int));
    int index;
    printf("Enter index: ");
    scanf("%d", &index);
    array[index] = 100;
    printf("Value at index %d is %d\n", index, array[index]);
    free(array);
    return 0;
}