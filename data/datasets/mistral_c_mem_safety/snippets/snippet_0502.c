#include <stdio.h>

#define ARRAY_SIZE 10

int get_element(int index) {
    int array[ARRAY_SIZE] = {0};
    if (index >= 0 && index < ARRAY_SIZE) {
        return array[index];
    } else {
        printf("Index out of bounds\n");
        return -1;
    }
}

int main() {
    int index;
    printf("Enter index: ");
    scanf("%d", &index);
    int element = get_element(index);
    if (element != -1) {
        printf("Element at index %d: %d\n", index, element);
    }
    return 0;
}