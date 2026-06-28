#include <stdio.h>
#include <string.h>

void parseData(char *data, int length) {
    if (length > 0 && length <= 100) {
        for (int i = 0; i < length; i++) {
            printf("%c", data[i]);
        }
        printf("\n");
    } else {
        printf("Invalid length\n");
    }
}

int main() {
    char data[] = "Hello, World!";
    int length = strlen(data);
    parseData(data, length);
    return 0;
}