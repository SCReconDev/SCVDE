#include <stdio.h>

void print_value(int* ptr) {
    if (ptr == NULL) {
        printf("Null pointer\n");
        return;
    }

    printf("Value: %d\n", *ptr);
}

int main() {
    int value = 42;
    int* ptr = &value;

    print_value(ptr);

    int* null_ptr = NULL;
    print_value(null_ptr);

    return 0;
}