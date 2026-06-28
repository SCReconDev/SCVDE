#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* username;
    char* password;
} User;

void decode_user(const char* cookie, User* user) {
    char* decoded = strdup(cookie);
    char* token = strtok(decoded, "&");
    user->username = strdup(strstr(token, "=") + 1);
    token = strtok(NULL, "&");
    user->password = strdup(strstr(token, "=") + 1);
    free(decoded);
}

void load_session(const char* cookie) {
    User user;
    decode_user(cookie, &user);
    printf("Session loaded for user: %s\n", user.username);
    free(user.username);
    free(user.password);
}

int main() {
    const char* cookie = "username=admin&password=123456";
    load_session(cookie);
    return 0;
}