#include <stdio.h>
#include <stdlib.h>

void print_element(int *array, int index) {
    printf("Element at index %d: %d\n", index, array[index]);
}

int main() {
    int *array = malloc(5 * sizeof(int));
    for (int i = 0; i < 5; i++) {
        array[i] = i * 10;
    }
    int user_index;
    printf("Enter index: ");
    scanf("%d", &user_index);
    print_element(array, user_index);
    free(array);
    return 0;
}