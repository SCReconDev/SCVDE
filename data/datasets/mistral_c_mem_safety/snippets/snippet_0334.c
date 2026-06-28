#include <stdio.h>
#include <stdlib.h>

void process_data(int *data) {
    printf("Processing data...\n");
}

int main() {
    int *data = (int *)malloc(10 * sizeof(int));
    if (data == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }
    process_data(data);
    return 0;
}