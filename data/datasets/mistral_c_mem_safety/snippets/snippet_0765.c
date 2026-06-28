#include <stdio.h>

void process_pointer(int* ptr) {
    if (ptr == NULL) {
        printf("Null pointer\n");
        return;
    }

    printf("Pointer value: %d\n", *ptr);
}

int main() {
    int value = 42;
    int* ptr = &value;

    process_pointer(ptr);

    int* null_ptr = NULL;
    process_pointer(null_ptr);

    return 0;
}