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
    char user_data[100];
    printf("Enter data: ");
    fgets(user_data, sizeof(user_data), stdin);
    int user_length;
    printf("Enter length: ");
    scanf("%d", &user_length);
    parse_data(user_data, user_length);
    return 0;
}