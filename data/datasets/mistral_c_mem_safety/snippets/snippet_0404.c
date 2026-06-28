#include <stdio.h>
#include <stdlib.h>

void process_data(int *data, int size) {
    for (int i = 0; i < size; i++) {
        printf("Data[%d]: %d\n", i, data[i]);
    }
}

int main() {
    int *data = (int *)malloc(5 * sizeof(int));
    if (data != NULL) {
        for (int i = 0; i < 5; i++) {
            data[i] = i * 2;
        }
        process_data(data, 5);
    }
    return 0;
}