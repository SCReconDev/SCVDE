#include <stdio.h>
#include <string.h>

void parse_data(char *data, int length) {
    if (length > 0 && length < 100) {
        printf("Parsed data: %.*s\n", length, data);
    }
}

int main() {
    char data[100];
    int length;
    printf("Enter your data: ");
    fgets(data, sizeof(data), stdin);
    printf("Enter the length: ");
    scanf("%d", &length);
    parse_data(data, length);
    return 0;
}