#include <stdio.h>
#include <string.h>

void parse_data(char *data, int length) {
    if (length > 0 && length < 100) {
        printf("Data: %s\n", data);
    }
}

int main() {
    char data[100];
    int length;
    printf("Enter data length: ");
    scanf("%d", &length);
    printf("Enter data: ");
    fgets(data, sizeof(data), stdin);
    parse_data(data, length);
    return 0;
}