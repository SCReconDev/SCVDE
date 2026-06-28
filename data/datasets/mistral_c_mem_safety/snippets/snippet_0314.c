#include <stdio.h>
#include <stdlib.h>

void process_data(int *data) {
    printf("Processing data...\n");
}

int main() {
    int *data = (int *)malloc(10 * sizeof(int));
    process_data(data);
    return 0;
}