#include <stdio.h>

void printValue(int *ptr) {
    if (ptr == NULL) {
        printf("Null pointer\n");
        return;
    }
    printf("Value: %d\n", *ptr);
}

int main() {
    int value = 10;
    int *ptr = &value;
    printValue(ptr);
    printValue(NULL);
    return 0;
}