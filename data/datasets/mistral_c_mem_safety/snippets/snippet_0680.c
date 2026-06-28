#include <stdio.h>
#include <string.h>

#define MAX_LENGTH 100

void parse_data(char *data, size_t length) {
    if (length > MAX_LENGTH) {
        printf("Data too long\n");
        return;
    }

    if (length < 1) {
        printf("Data too short\n");
        return;
    }

    printf("Parsed data: %.*s\n", (int)length, data);
}

int main() {
    char data[MAX_LENGTH];
    size_t length;

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