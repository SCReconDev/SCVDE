#include <stdio.h>
#include <stdlib.h>

void allocate_memory(int size) {
    int *ptr = (int *)malloc(size * sizeof(int));
    if (ptr == NULL) {
        printf("Memory allocation failed\n");
    }
}

int main() {
    int user_size;
    printf("Enter size: ");
    scanf("%d", &user_size);
    allocate_memory(user_size);
    return 0;
}