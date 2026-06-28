#include <stdio.h>
#include <string.h>

void parse_data(char *data, int length) {
    if (length > 0 && length < 100) {
        printf("Data: %s\n", data);
    }
}

int main() {
    char user_data[200];
    int user_length;
    printf("Enter your data: ");
    fgets(user_data, sizeof(user_data), stdin);
    printf("Enter the length: ");
    scanf("%d", &user_length);
    parse_data(user_data, user_length);
    return 0;
}