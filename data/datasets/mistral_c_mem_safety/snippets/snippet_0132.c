#include <stdio.h>
#include <stdlib.h>

void print_element(int *array, int index) {
    printf("Element at index %d: %d\n", index, array[index]);
}

int main() {
    int *numbers = (int *)malloc(5 * sizeof(int));
    for (int i = 0; i < 5; i++) {
        numbers[i] = i * 10;
    }
    int user_index;
    printf("Enter the index to print: ");
    scanf("%d", &user_index);
    print_element(numbers, user_index);
    free(numbers);
    return 0;
}