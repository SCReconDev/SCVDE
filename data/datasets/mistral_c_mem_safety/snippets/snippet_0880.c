#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void parse_data(char *data, size_t length) {
    if (length < 1 || length > 100) {
        printf("Invalid length\n");
        return;
    }
    for (size_t i = 0; i < length; i++) {
        printf("Data character at index %zu: %c\n", i, data[i]);
    }
}

int main() {
    char data[100];
    size_t length;
    printf("Enter data: ");
    fgets(data, sizeof(data), stdin);
    length = strlen(data);
    if (data[length - 1] == '\n') {
        data[length - 1] = '\0';
        length--;
    }
    parse_data(data, length);
    return 0;
}