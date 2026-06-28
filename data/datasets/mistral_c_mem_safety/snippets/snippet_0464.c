#include <stdio.h>
#include <stdlib.h>

void process_data(int *data) {
    printf("Processing data: %d\n", *data);
}

int main() {
    int *data = malloc(sizeof(int));
    *data = 42;
    process_data(data);
    free(data);
    return 0;
}