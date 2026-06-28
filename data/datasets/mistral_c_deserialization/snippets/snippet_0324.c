#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char username[50];
    char password[50];
} User;

void decode_user(const char* data, User* user) {
    sscanf(data, "%49[^|]|%49[^|]", user->username, user->password);
}

int main() {
    char cookie[100];
    User user;

    printf("Enter cookie data (username|password): ");
    fgets(cookie, sizeof(cookie), stdin);
    cookie[strcspn(cookie, "\n")] = '\0';

    decode_user(cookie, &user);

    printf("Username: %s\nPassword: %s\n", user.username, user.password);

    return 0;
}