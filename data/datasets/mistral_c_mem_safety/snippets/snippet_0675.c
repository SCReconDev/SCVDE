#include <stdio.h>

void print_value(int *value) {
    if (value == NULL) {
        printf("Null pointer\n");
        return;
    }

    printf("Value: %d\n", *value);
}

int main() {
    int num = 42;
    int *ptr = &num;

    print_value(ptr);
    print_value(NULL);

    return 0;
}