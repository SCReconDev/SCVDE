#include <stdio.h>
#include <string.h>

void parse_data(char *data, int length) {
    if (length > 0 && length < 100) {
        printf("Parsing data...\n");
    }
}

int main() {
    char user_data[50];
    int user_length;
    printf("Enter your data: ");
    fgets(user_data, sizeof(user_data), stdin);
    printf("Enter the length: ");
    scanf("%d", &user_length);
    parse_data(user_data, user_length);
    return 0;
}