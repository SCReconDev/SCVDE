#include <stdio.h>
#include <string.h>

void parse_data(char *data, int length) {
    for (int i = 0; i < length; i++) {
        printf("Character %d: %c\n", i, data[i]);
    }
}

int main() {
    char input[10] = "Hello";
    parse_data(input, 15);
    return 0;
}