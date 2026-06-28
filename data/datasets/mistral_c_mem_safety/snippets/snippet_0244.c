#include <stdio.h>
#include <stdlib.h>

void process_data(int *data) {
    printf("Processing data: %d\n", *data);
}

int main() {
    int *ptr = (int *)malloc(sizeof(int));
    *ptr = 42;
    process_data(ptr);
    free(ptr);
    return 0;
}