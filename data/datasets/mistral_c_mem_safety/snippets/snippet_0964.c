#include <stdio.h>
#include <stdlib.h>

void process_data() {
    int *data = (int *)malloc(sizeof(int) * 10);

    if (data == NULL) {
        printf("Memory allocation failed\n");
        return;
    }

    for (int i = 0; i < 10; i++) {
        data[i] = i;
    }

    printf("Data processed\n");
    free(data);
}

int main() {
    process_data();
    return 0;
}