#include <stdio.h>
#include <string.h>

void parse_data(char *data, int length) {
    if (length < 0 || length > 100) {
        printf("Invalid length\n");
        return;
    }
    char buffer[length];
    strncpy(buffer, data, length);
    printf("Parsed data: %s\n", buffer);
}

int main() {
    char user_data[100];
    int user_length;
    printf("Enter your data: ");
    fgets(user_data, sizeof(user_data), stdin);
    printf("Enter the length: ");
    scanf("%d", &user_length);
    parse_data(user_data, user_length);
    return 0;
}