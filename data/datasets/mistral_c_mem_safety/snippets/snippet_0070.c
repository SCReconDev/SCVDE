#include <stdio.h>
#include <string.h>

void parse_data(char *data, int length) {
    if (length > 0 && length < 100) {
        char buffer[length];
        strcpy(buffer, data);
        printf("Parsed data: %s\n", buffer);
    }
}

int main() {
    char user_data[200];
    printf("Enter your data: ");
    fgets(user_data, sizeof(user_data), stdin);
    parse_data(user_data, strlen(user_data));
    return 0;
}