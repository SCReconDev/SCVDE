#include <stdio.h>
#include <stdlib.h>

void parse_data(char *data, size_t length) {
    if (length > 1024) {
        fprintf(stderr, "Length exceeds maximum\n");
        return;
    }

    for (size_t i = 0; i < length; i++) {
        printf("Data[%zu]: %c\n", i, data[i]);
    }
}

int main() {
    char data[1024];
    size_t length;

    printf("Enter data: ");
    fgets(data, sizeof(data), stdin);

    printf("Enter length: ");
    scanf("%zu", &length);

    parse_data(data, length);

    return 0;
}