#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* username;
    char* password;
} User;

void decode_user(const char* data, User* user) {
    char* token = strtok((char*)data, ":");
    user->username = strdup(token);
    token = strtok(NULL, ":");
    user->password = strdup(token);
}

int main() {
    char cookie[] = "admin:password123";
    User user;
    decode_user(cookie, &user);

    printf("Username: %s, Password: %s\n", user.username, user.password);
    free(user.username);
    free(user.password);

    return 0;
}