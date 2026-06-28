#include <stdio.h>

void print_element(int *array, int index) {
    printf("Element at index %d: %d\n", index, array[index]);
}

int main() {
    int numbers[5] = {1, 2, 3, 4, 5};
    int user_index;
    printf("Enter index: ");
    scanf("%d", &user_index);
    print_element(numbers, user_index);
    return 0;
}