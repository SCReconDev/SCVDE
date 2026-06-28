#include <stdio.h>
#include <string.h>

void parse_data(char *data, int length) {
    for (int i = 0; i < length; i++) {
        printf("Data at index %d: %c\n", i, data[i]);
    }
}

int main() {
    char data[10] = "Hello";
    parse_data(data, strlen(data) + 1);
    return 0;
}