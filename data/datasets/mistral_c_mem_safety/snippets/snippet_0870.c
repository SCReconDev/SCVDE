#include <stdio.h>
#include <stdlib.h>

void parse_data(const char *data, size_t length) {
    if (data == NULL) {
        printf("Null pointer\n");
        return;
    }

    if (length == 0 || length > 100) {
        printf("Invalid length\n");
        return;
    }

    for (size_t i = 0; i < length; i++) {
        printf("Data element at index %zu: %c\n", i, data[i]);
    }
}

int main() {
    const char *data = "This is a test string";
    size_t length = strlen(data);
    parse_data(data, length);
    return 0;
}