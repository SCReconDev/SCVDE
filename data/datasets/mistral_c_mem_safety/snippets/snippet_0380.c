#include <stdio.h>
#include <string.h>

void parse_data(char *data, int length) {
    for (int i = 0; i < length; i++) {
        printf("%c", data[i]);
    }
}

int main() {
    char data[10] = "Hello";
    parse_data(data, 15);
    return 0;
}