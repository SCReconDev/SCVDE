#include <stdio.h>
#include <stdlib.h>

void parse_data(char *data, size_t length) {
    if (length > 100) {
        fprintf(stderr, "Data length too large\n");
        return;
    }

    printf("Parsed data: ");
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