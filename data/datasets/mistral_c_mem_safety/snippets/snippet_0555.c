#include <stdio.h>
#include <stdlib.h>

void process_pointer(int *ptr) {
    if (ptr != NULL) {
        printf("Value: %d\n", *ptr);
    } else {
        printf("Null pointer provided.\n");
    }
}

int main() {
    int value = 10;
    int *ptr = &value;
    process_pointer(ptr);
    process_pointer(NULL);
    return 0;
}