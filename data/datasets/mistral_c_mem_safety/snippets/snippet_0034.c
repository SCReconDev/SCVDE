#include <stdio.h>
#include <stdlib.h>

void process_data(int *data, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", data[i]);
    }
    printf("\n");
}

int main() {
    int *data = (int *)malloc(10 * sizeof(int));
    for (int i = 0; i < 10; i++) {
        data[i] = i;
    }
    process_data(data, 10);
    return 0;
}