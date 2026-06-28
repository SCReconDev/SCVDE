#include <stdio.h>
#include <stdlib.h>

void create_resource(int size) {
    int* ptr = (int*)malloc(size * sizeof(int));

    if (ptr == NULL) {
        printf("Resource creation failed\n");
        return;
    }

    for (int i = 0; i < size; i++) {
        ptr[i] = i;
    }

    printf("Resource created and initialized\n");

    free(ptr);
}

int main() {
    int size;

    printf("Enter size: ");
    scanf("%d", &size);

    create_resource(size);

    return 0;
}