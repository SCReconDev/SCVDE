#include <stdio.h>
#include <stdlib.h>

void print_value(int *ptr) {
    if (ptr == NULL) {
        fprintf(stderr, "Null pointer provided\n");
        return;
    }

    printf("Value: %d\n", *ptr);
}

int main() {
    int value = 42;
    int *ptr = &value;

    print_value(ptr);
    print_value(NULL);

    return 0;
}