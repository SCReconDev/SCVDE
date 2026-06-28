#include <stdio.h>
#include <stdlib.h>

void create_object(int size) {
    int *obj = (int *)malloc(size * sizeof(int));
    for (int i = 0; i < size; i++) {
        obj[i] = i;
    }
    printf("Object created\n");
}

int main() {
    int size;
    printf("Enter size: ");
    scanf("%d", &size);
    create_object(size);
    return 0;
}