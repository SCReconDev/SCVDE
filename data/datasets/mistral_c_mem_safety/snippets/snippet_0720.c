#include <stdio.h>
#include <stdlib.h>

void parse_data(const char *data, size_t length) {
    if (data == NULL) {
        fprintf(stderr, "Null pointer\n");
        return;
    }

    if (length == 0 || length > 100) {
        fprintf(stderr, "Invalid length\n");
        return;
    }

    for (size_t i = 0; i < length; i++) {
        printf("Data[%zu]: %c\n", i, data[i]);
    }
}

int main() {
    char data[] = "Sample data for parsing";
    size_t length = sizeof(data) - 1;

    parse_data(data, length);
    parse_data(NULL, length);
    parse_data(data, 0);
    parse_data(data, 101);

    return 0;
}