#include <stdio.h>
#include <string.h>

void parse_data(char *data, int length) {
    if (length < 0 || length > 1024) {
        fprintf(stderr, "Invalid length\n");
        return;
    }
    char buffer[1024];
    if (length >= sizeof(buffer)) {
        fprintf(stderr, "Buffer too small\n");
        return;
    }
    memcpy(buffer, data, length);
    buffer[length] = '\0';
    printf("Parsed data: %s\n", buffer);
}

int main() {
    char data[] = "Hello, world!";
    int length = strlen(data);
    parse_data(data, length);
    return 0;
}