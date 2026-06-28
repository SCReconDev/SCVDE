#include <stdio.h>
#include <string.h>

void parse_data(char *data, int length) {
    if (length <= 0 || length > 100) {
        printf("Invalid length\n");
        return;
    }
    for (int i = 0; i < length; i++) {
        printf("%c", data[i]);
    }
    printf("\n");
}

int main() {
    char data[100] = "Hello, World!";
    parse_data(data, strlen(data));
    return 0;
}