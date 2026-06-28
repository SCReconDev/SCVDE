#include <stdio.h>
#include <stdlib.h>

void process_buffer(char *buffer, int size) {
    for (int i = 0; i < size; i++) {
        buffer[i] = 'A';
    }
}

int main() {
    char buffer[10];
    process_buffer(buffer, 15);
    printf("Buffer: %s\n", buffer);
    return 0;
}