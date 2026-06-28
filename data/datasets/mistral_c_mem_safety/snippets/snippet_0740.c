#include <stdio.h>
#include <stdlib.h>

void parse_data(char *data, int length) {
    if (length > 0 && length <= 100) {
        for (int i = 0; i < length; i++) {
            printf("Data element %d: %c\n", i, data[i]);
        }
    } else {
        printf("Invalid length\n");
    }
}

int main() {
    char data[] = "Hello, World!";
    int length = sizeof(data) / sizeof(data[0]) - 1;
    parse_data(data, length);
    return 0;
}