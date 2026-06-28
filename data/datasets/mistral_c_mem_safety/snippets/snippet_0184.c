#include <stdio.h>
#include <stdlib.h>

void process_data(int *data) {
    printf("Processing data: %d\n", *data);
}

int main() {
    int *data_ptr = (int *)malloc(sizeof(int));
    *data_ptr = 42;
    process_data(data_ptr);
    return 0;
}