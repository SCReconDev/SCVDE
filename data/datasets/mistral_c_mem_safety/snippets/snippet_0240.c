#include <stdio.h>
#include <string.h>

void parse_data(char *data, int length) {
    if (length < 10) {
        printf("Invalid length.\n");
        return;
    }
    char buffer[10];
    strncpy(buffer, data, length);
    printf("Parsed data: %s\n", buffer);
}

int main() {
    char user_data[20];
    int user_length;
    printf("Enter data: ");
    fgets(user_data, sizeof(user_data), stdin);
    printf("Enter length: ");
    scanf("%d", &user_length);
    parse_data(user_data, user_length);
    return 0;
}