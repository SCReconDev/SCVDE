#include <stdio.h>
#include <string.h>

void parseData(char *data, int length) {
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
    char data[] = "Hello, World!";
    int length = strlen(data);
    parseData(data, length);
    parseData(data, 200);
    return 0;
}