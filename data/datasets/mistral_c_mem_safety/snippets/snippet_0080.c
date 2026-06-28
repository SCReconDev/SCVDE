#include <stdio.h>
#include <string.h>

void parse_data(char* data, int length) {
    if (length > 0 && length < 100) {
        char buffer[length];
        strcpy(buffer, data);
        printf("Parsed data: %s\n", buffer);
    } else {
        printf("Invalid length\n");
    }
}

int main() {
    char data[100] = "Sample data";
    int length;
    printf("Enter the length: ");
    scanf("%d", &length);
    parse_data(data, length);
    return 0;
}