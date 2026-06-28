#include <stdio.h>

void print_value(int *ptr) {
    printf("Value: %d\n", *ptr);
}

int main() {
    int *ptr = NULL;
    print_value(ptr);
    return 0;
}