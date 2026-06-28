#include <stdio.h>

void parse_data(char *data, int length) {
    if (length > 0 && length <= 100) {
        for (int i = 0; i < length; i++) {
            printf("Data[%d]: %c\n", i, data[i]);
        }
    } else {
        printf("Invalid length\n");
    }
}

int main() {
    char data[100] = "Hello, World!";
    int length = strlen(data);
    parse_data(data, length);
    return 0;
}