#include <stdio.h>
#include <stdlib.h>

void safeResourceCleanup(int **ptr) {
    if (*ptr != NULL) {
        free(*ptr);
        *ptr = NULL;
    }
}

int main() {
    int *ptr = (int*)malloc(10 * sizeof(int));
    if (ptr != NULL) {
        for (int i = 0; i < 10; i++) {
            ptr[i] = i;
        }
        safeResourceCleanup(&ptr);
    }
    return 0;
}