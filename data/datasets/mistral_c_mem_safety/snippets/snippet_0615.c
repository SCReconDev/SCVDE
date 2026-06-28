#include <stdio.h>

void safePointerDereference(int *ptr) {
    if (ptr != NULL) {
        printf("Value: %d\n", *ptr);
    } else {
        printf("Null pointer\n");
    }
}

int main() {
    int value = 42;
    int *ptr = &value;
    safePointerDereference(ptr);
    safePointerDereference(NULL);
    return 0;
}