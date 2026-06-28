#include <stdio.h>
#include <string.h>

void manipulate_buffer(char* buffer, size_t buffer_size, char* data, size_t data_size) {
    if (data_size <= buffer_size) {
        memcpy(buffer, data, data_size);
        buffer[data_size] = '\0';
    } else {
        printf("Data too large for buffer\n");
    }
}

int main() {
    char buffer[100];
    char data[] = "Hello, World!";
    manipulate_buffer(buffer, sizeof(buffer), data, strlen(data));
    printf("Buffer: %s\n", buffer);
    return 0;
}