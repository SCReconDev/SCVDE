#include <stdio.h>

void printValue(int *ptr) {
    if (ptr != NULL) {
        printf("Value: %d\n", *ptr);
    } else {
        printf("Null pointer.\n");
    }
}

int main() {
    int value = 42;
    int *ptr = &value;
    printValue(ptr);
    printValue(NULL);
    return 0;
}