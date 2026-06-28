#include <stdio.h>

#define ARRAY_SIZE 10

void access_array(int index) {
    int array[ARRAY_SIZE] = {0};
    if (index >= 0 && index < ARRAY_SIZE) {
        printf("Array element: %d\n", array[index]);
    } else {
        printf("Index out of bounds\n");
    }
}

int main() {
    int index;
    printf("Enter index: ");
    scanf("%d", &index);
    access_array(index);
    return 0;
}