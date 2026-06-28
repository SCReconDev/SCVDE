#include <stdio.h>
#include <stdlib.h>

void cleanup_memory(void* ptr) {
    if (ptr != NULL) {
        free(ptr);
        printf("Memory freed successfully\n");
    } else {
        fprintf(stderr, "Null pointer provided\n");
    }
}

int main() {
    void* ptr = malloc(1024);
    cleanup_memory(ptr);
    return 0;
}