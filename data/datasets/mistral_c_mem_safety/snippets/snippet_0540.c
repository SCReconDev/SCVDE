#include <stdio.h>
#include <stdlib.h>

void parse_data(const char* data, size_t length) {
    if (length < 1 || length > 100) {
        fprintf(stderr, "Invalid length\n");
        return;
    }

    for (size_t i = 0; i < length; i++) {
        printf("%c ", data[i]);
    }
    printf("\n");
}

int main() {
    const char* data = "Hello, World!";
    size_t length = 13;

    parse_data(data, length);

    return 0;
}