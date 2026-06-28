#include <stdio.h>

void print_value(int* ptr) {
    if (ptr != NULL) {
        printf("Value: %d\n", *ptr);
    } else {
        fprintf(stderr, "Null pointer\n");
    }
}

int main() {
    int value = 42;
    int* ptr = &value;

    print_value(ptr);

    ptr = NULL;
    print_value(ptr);

    return 0;
}