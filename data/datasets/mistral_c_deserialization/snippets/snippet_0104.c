#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* username;
    char* password;
} User;

void load_user(User* user, const char* cookie) {
    char* token = strdup(cookie);
    char* part = strtok(token, "|");
    user->username = strdup(part);
    part = strtok(NULL, "|");
    user->password = strdup(part);
    free(token);
}

int main() {
    char* cookie = "admin|password123";
    User user;
    load_user(&user, cookie);
    printf("Username: %s, Password: %s\n", user->username, user->password);
    return 0;
}