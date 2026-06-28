#include <stdio.h>
#include <string.h>

void parseData(const char *data, size_t length) {
    if (data == NULL) {
        printf("Null data provided.\n");
        return;
    }

    if (length == 0 || length > 100) {
        printf("Invalid length provided.\n");
        return;
    }

    for (size_t i = 0; i < length; i++) {
        printf("%c", data[i]);
    }
    printf("\n");
}

int main() {
    const char *data = "Hello, World!";
    size_t length = strlen(data);

    parseData(data, length);
    parseData(NULL, length);
    parseData(data, 0);
    parseData(data, 101);

    return 0;
}