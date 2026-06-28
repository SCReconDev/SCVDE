#include <stdio.h>
#include <stdlib.h>

void print_element(int* array, int index) {
    printf("Element at index %d: %d\n", index, array[index]);
}

int main() {
    int array[5] = {1, 2, 3, 4, 5};
    int user_index;
    printf("Enter index: ");
    scanf("%d", &user_index);
    print_element(array, user_index);
    return 0;
}