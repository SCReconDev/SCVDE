#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char username[50];
    char password[50];
} User;

void decode_user(User *user, const char *cookie) {
    char *token = strtok((char *)cookie, ":");
    if (token != NULL) {
        strncpy(user->username, token, sizeof(user->username) - 1);
        token = strtok(NULL, ":");
        if (token != NULL) {
            strncpy(user->password, token, sizeof(user->password) - 1);
        }
    }
}

int main() {
    char cookie[100];
    User user;

    printf("Enter cookie: ");
    fgets(cookie, sizeof(cookie), stdin);

    decode_user(&user, cookie);

    printf("Decoded User: Username=%s, Password=%s\n", user.username, user.password);

    return 0;
}