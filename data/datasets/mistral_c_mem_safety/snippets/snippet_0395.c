#include <stdio.h>

void print_value(int *ptr) {
    printf("Value: %d\n", *ptr);
}

int main() {
    int *null_ptr = NULL;
    print_value(null_ptr);
    return 0;
}