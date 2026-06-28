#include <stdio.h>

void dereference_pointer(int *ptr) {
    printf("Value: %d\n", *ptr);
}

int main() {
    int *ptr = NULL;
    dereference_pointer(ptr);
    return 0;
}