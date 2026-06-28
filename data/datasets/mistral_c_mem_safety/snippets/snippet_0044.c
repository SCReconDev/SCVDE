#include <stdio.h>
#include <stdlib.h>

void process_data(int *data) {
    for (int i = 0; i < 10; i++) {
        printf("Data: %d\n", data[i]);
    }
}

int main() {
    int *data = (int*)malloc(10 * sizeof(int));
    for (int i = 0; i < 10; i++) {
        data[i] = i;
    }
    process_data(data);
    return 0;
}