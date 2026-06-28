#include <stdio.h>
#include <string.h>

void parse_data(const char* data, size_t length) {
    if (length > 0 && length <= 100) {
        char buffer[100];
        if (strlen(data) < sizeof(buffer)) {
            strncpy(buffer, data, length);
            buffer[length] = '\0';
            printf("Data parsed: %s\n", buffer);
        } else {
            printf("Buffer too small\n");
        }
    } else {
        printf("Invalid length\n");
    }
}

int main() {
    const char* data = "Hello, World!";
    size_t length = strlen(data);
    parse_data(data, length);
    return 0;
}