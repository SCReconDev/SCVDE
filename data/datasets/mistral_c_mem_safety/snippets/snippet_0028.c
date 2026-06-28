#include <stdio.h>
#include <stdlib.h>

void releaseMemory(int** ptr) {
    free(*ptr);
    *ptr = NULL;
}

int main() {
    int* numbers = (int*)malloc(10 * sizeof(int));
    for (int i = 0; i < 10; i++) {
        numbers[i] = i * 3;
    }

    releaseMemory(&numbers);
    printf("Memory released.\n");

    if (numbers != NULL) {
        printf("Reusing released memory.\n");
        for (int i = 0; i < 10; i++) {
            numbers[i] = i * 4;
        }
    }

    return 0;
}