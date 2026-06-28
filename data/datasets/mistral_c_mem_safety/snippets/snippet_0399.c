#include <stdio.h>
#include <stdlib.h>

void create_object(int size) {
    int *ptr = (int *)malloc(size * sizeof(int));
    if (ptr != NULL) {
        for (int i = 0; i < size; i++) {
            ptr[i] = i;
        }
    }
}

int main() {
    create_object(10);
    return 0;
}