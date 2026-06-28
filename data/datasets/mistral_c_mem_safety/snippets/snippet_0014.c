#include <stdio.h>
#include <stdlib.h>

void create_buffer(int size) {
    int *buffer = (int *)malloc(size * sizeof(int));
    for (int i = 0; i < size; i++) {
        buffer[i] = i;
    }
    printf("Buffer created and initialized\n");
}

int main() {
    int user_size;
    printf("Enter the size: ");
    scanf("%d", &user_size);
    create_buffer(user_size);
    return 0;
}