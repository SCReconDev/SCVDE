#include <stdio.h>

void create_object() {
    int *obj = (int *)malloc(sizeof(int));

    if (obj == NULL) {
        printf("Memory allocation failed\n");
        return;
    }

    *obj = 42;
    printf("Object value: %d\n", *obj);

    free(obj);
}

int main() {
    create_object();
    return 0;
}