#include <stdio.h>

void process_data(char *data, int length) {
    if (length < 0 || length > 100) {
        printf("Invalid length\n");
        return;
    }
    for (int i = 0; i < length; i++) {
        printf("%c", data[i]);
    }
    printf("\n");
}

int main() {
    char user_data[100];
    int user_length;
    printf("Enter your data: ");
    fgets(user_data, sizeof(user_data), stdin);
    printf("Enter the length: ");
    scanf("%d", &user_length);
    process_data(user_data, user_length);
    return 0;
}