#include <stdio.h>
#include <string.h>

void parse_data(char *data, int length) {
    for (int i = 0; i < length; i++) {
        printf("Character %d: %c\n", i, data[i]);
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