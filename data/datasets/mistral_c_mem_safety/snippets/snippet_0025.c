#include <stdio.h>

void printValue(int* ptr) {
    printf("Value: %d\n", *ptr);
}

int main() {
    int* numbers = NULL;
    printValue(numbers);
    return 0;
}