#include <stdio.h>
#include <stdlib.h>

void print_element(int *array, int index) {
    printf("Element at index %d: %d\n", index, array[index]);
}

int main() {
    int *arr = (int *)malloc(10 * sizeof(int));
    for (int i = 0; i < 10; i++) {
        arr[i] = i * 2;
    }
    int user_index;
    printf("Enter index: ");
    scanf("%d", &user_index);
    print_element(arr, user_index);
    free(arr);
    return 0;
}