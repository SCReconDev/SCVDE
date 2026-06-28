#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void parse_data(const char *data, size_t length) {
    if (length > 100) {
        fprintf(stderr, "Data length exceeds maximum allowed\n");
        return;
    }

    for (size_t i = 0; i < length; i++) {
        printf("Data[%zu]: %c\n", i, data[i]);
    }
}

int main() {
    const char *data = "Sample data for parsing";
    size_t length = strlen(data);
    parse_data(data, length);
    return 0;
}