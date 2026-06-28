#include <stdio.h>
#include <string.h>

#define MAX_LENGTH 100

void parse_data(char *data, int length) {
    if (length <= 0 || length > MAX_LENGTH) {
        printf("Invalid length\n");
        return;
    }
    char buffer[MAX_LENGTH];
    strncpy(buffer, data, length);
    buffer[length] = '\0';
    printf("Parsed data: %s\n", buffer);
}

int main() {
    char data[MAX_LENGTH];
    int length;
    printf("Enter data: ");
    fgets(data, MAX_LENGTH, stdin);
    length = strlen(data);
    if (data[length - 1] == '\n') {
        data[length - 1] = '\0';
        length--;
    }
    parse_data(data, length);
    return 0;
}