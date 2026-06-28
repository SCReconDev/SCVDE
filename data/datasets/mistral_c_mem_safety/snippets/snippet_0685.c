#include <stdio.h>

void print_value(int *ptr) {
    if (ptr != NULL) {
        printf("Value: %d\n", *ptr);
    } else {
        printf("Null pointer\n");
    }
}

int main() {
    int value = 42;
    int *ptr = &value;
    print_value(ptr);
    print_value(NULL);
    return 0;
}