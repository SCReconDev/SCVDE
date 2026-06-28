#include <stdio.h>
#include <stdlib.h>

void process_data(const char *data, size_t length) {
    if (data == NULL) {
        printf("Null data\n");
        return;
    }

    if (length == 0 || length > 100) {
        printf("Invalid length\n");
        return;
    }

    printf("Processing data of length %zu\n", length);
    for (size_t i = 0; i < length; i++) {
        printf("%c", data[i]);
    }
    printf("\n");
}

int main() {
    const char *data = "Hello, World!";
    process_data(data, strlen(data));
    return 0;
}