#include <stdio.h>

void print_value(int *ptr) {
    if (ptr == NULL) {
        printf("Null pointer\n");
        return;
    }

    printf("Value: %d\n", *ptr);
}

int main() {
    int value = 42;
    print_value(&value);
    return 0;
}