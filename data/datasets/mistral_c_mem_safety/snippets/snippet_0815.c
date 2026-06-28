#include <stdio.h>

void print_value(int *ptr) {
    if (ptr != NULL) {
        printf("Value: %d\n", *ptr);
    } else {
        printf("Pointer is NULL\n");
    }
}

int main() {
    int value = 10;
    int *ptr = &value;
    print_value(ptr);
    ptr = NULL;
    print_value(ptr);
    return 0;
}