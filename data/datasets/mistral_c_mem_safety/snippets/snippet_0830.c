#include <stdio.h>
#include <string.h>

void parse_data(char *data, int length) {
    if (length < 0 || length > 100) {
        printf("Invalid length\n");
        return;
    }
    for (int i = 0; i < length; i++) {
        printf("Data[%d]: %c\n", i, data[i]);
    }
}

int main() {
    char data[] = "Hello, World!";
    int length = strlen(data);
    parse_data(data, length);
    return 0;
}