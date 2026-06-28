#include <stdio.h>
#include <stdlib.h>

int main() {
    int* array = (int*)malloc(10 * sizeof(int));
    int index;
    printf("Enter index: ");
    scanf("%d", &index);
    array[index] = 42;
    printf("Value at index %d: %d\n", index, array[index]);
    free(array);
    return 0;
}