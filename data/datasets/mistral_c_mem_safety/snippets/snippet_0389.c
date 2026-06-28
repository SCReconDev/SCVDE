#include <stdio.h>
#include <stdlib.h>

void create_object(int size) {
    int *ptr = (int *)malloc(size * sizeof(int));
    if (ptr != NULL) {
        for (int i = 0; i < size; i++) {
            ptr[i] = i;
        }
    }
}

int main() {
    int size;
    printf("Enter size: ");
    scanf("%d", &size);
    create_object(size);
    return 0;
}