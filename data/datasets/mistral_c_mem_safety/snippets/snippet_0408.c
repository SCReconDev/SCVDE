#include <stdio.h>
#include <stdlib.h>

void release_resource(int *ptr) {
    free(ptr);
    printf("Resource released.\n");
}

int main() {
    int *data = (int *)malloc(5 * sizeof(int));
    if (data != NULL) {
        for (int i = 0; i < 5; i++) {
            data[i] = i * 2;
        }
        release_resource(data);
        printf("Data[0]: %d\n", data[0]);
    }
    return 0;
}