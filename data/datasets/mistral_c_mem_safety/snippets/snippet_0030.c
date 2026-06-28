#include <stdio.h>
#include <string.h>

void parseData(char* data, int length) {
    if (length > 0 && length <= 100) {
        printf("Parsed data: %.*s\n", length, data);
    }
}

int main() {
    char userData[100];
    int dataLength;
    printf("Enter your data: ");
    fgets(userData, sizeof(userData), stdin);
    printf("Enter the length of the data: ");
    scanf("%d", &dataLength);
    parseData(userData, dataLength);
    return 0;
}