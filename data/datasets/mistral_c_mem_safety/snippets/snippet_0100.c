#include <stdio.h>

void parse_data(char *data, int length) {
    for (int i = 0; i < length; i++) {
        printf("%c", data[i]);
    }
    printf("\n");
}

int main() {
    char data[10] = "Hello";
    int user_length;
    printf("Enter length: ");
    scanf("%d", &user_length);
    parse_data(data, user_length);
    return 0;
}