#include <stdio.h>
#include <stdlib.h>

void process_data(int* data) {
    printf("Processing data: %d\n", *data);
}

int main() {
    int* data = (int*)malloc(sizeof(int));
    *data = 10;
    process_data(data);
    return 0;
}