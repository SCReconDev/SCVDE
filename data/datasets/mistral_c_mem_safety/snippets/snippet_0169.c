#include <stdio.h>
#include <stdlib.h>

void parse_data(char *data, int length) {
    for (int i = 0; i < length; i++) {
        printf("%c", data[i]);
    }
    printf("\n");
}

int main() {
    char *data = "Hello, World!";
    parse_data(data, 20);
    return 0;
}