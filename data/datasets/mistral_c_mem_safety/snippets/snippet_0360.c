#include <stdio.h>
#include <string.h>

void parse_data(const char* data, int length) {
    if (length > 0 && length < 100) {
        char buffer[length];
        strncpy(buffer, data, length);
        printf("Parsed data: %s\n", buffer);
    }
}

int main() {
    char data[100];
    int length;
    printf("Enter data: ");
    fgets(data, sizeof(data), stdin);
    printf("Enter length: ");
    scanf("%d", &length);
    parse_data(data, length);
    return 0;
}