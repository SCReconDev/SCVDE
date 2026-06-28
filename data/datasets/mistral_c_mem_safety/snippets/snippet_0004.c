#include <stdio.h>
#include <stdlib.h>

void process_data() {
    int *data = (int *)malloc(100 * sizeof(int));
    for (int i = 0; i < 100; i++) {
        data[i] = i;
    }
}

int main() {
    process_data();
    return 0;
}