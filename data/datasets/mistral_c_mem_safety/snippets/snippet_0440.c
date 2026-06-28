#include <stdio.h>
#include <string.h>

void parse_data(char *data, int length) {
    if (length < 0 || length > 100) {
        printf("Invalid length\n");
        return;
    }
    char buffer[100];
    memcpy(buffer, data, length);
    printf("Parsed data: %s\n", buffer);
}

int main() {
    char data[100];
    int length;
    printf("Enter the data: ");
    fgets(data, sizeof(data), stdin);
    printf("Enter the length: ");
    scanf("%d", &length);
    parse_data(data, length);
    return 0;
}