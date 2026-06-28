#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* username;
    char* password;
} User;

void deserialize_user(char* data, User* user) {
    char* token = strtok(data, ":");
    user->username = strdup(token);
    token = strtok(NULL, ":");
    user->password = strdup(token);
}

void load_session(char* cookie) {
    User user;
    deserialize_user(cookie, &user);
    printf("Username: %s, Password: %s\n", user.username, user.password);
    free(user.username);
    free(user.password);
}

int main() {
    char* cookie = "admin:password123";
    load_session(cookie);
    return 0;
}