#include <stdio.h>
#include <stdlib.h>

void parse_data(char *data, int length) {
    if (length < 0 || length > 100) {
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
    int length;
    printf("Enter length: ");
    scanf("%d", &length);
    parse_data(data, length);
    return 0;
}