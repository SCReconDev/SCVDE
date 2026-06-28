#include <stdio.h>
#include <stdlib.h>

void process_data(int *data) {
    printf("Processing data: %d\n", *data);
}

int main() {
    int *data = NULL;
    process_data(data);
    return 0;
}