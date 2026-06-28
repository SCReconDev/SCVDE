#include <stdio.h>
#include <stdlib.h>

void processData() {
    int *data = (int *)malloc(10 * sizeof(int));

    if (data == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }

    for (int i = 0; i < 10; i++) {
        data[i] = i;
    }

    for (int i = 0; i < 10; i++) {
        printf("%d ", data[i]);
    }
    printf("\n");

    free(data);
}

int main() {
    processData();
    return 0;
}