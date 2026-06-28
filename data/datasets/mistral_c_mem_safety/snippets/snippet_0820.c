#include <stdio.h>
#include <string.h>

void parse_data(const char *data, size_t length) {
    if (length > 100) {
        printf("Data length is too long\n");
        return;
    }
    for (size_t i = 0; i < length; i++) {
        printf("%c", data[i]);
    }
    printf("\n");
}

int main() {
    char data[] = "Hello, World!";
    parse_data(data, strlen(data));
    return 0;
}