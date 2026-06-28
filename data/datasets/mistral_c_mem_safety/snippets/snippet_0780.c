#include <stdio.h>
#include <string.h>

void parse_data(const char* data, size_t length) {
    if (length > 0 && length <= 1024) {
        char buffer[1024];
        memcpy(buffer, data, length);
        buffer[length] = '\0';
        printf("Parsed data: %s\n", buffer);
    } else {
        fprintf(stderr, "Invalid length\n");
    }
}

int main() {
    const char* data = "Hello, World!";
    parse_data(data, strlen(data));
    return 0;
}