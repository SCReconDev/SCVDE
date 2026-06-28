#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* username;
    char* password;
} User;

void decode_user(const char* cookie, User* user) {
    char* token = strtok((char*)cookie, "&");
    user->username = strdup(strchr(token, '=') + 1);
    token = strtok(NULL, "&");
    user->password = strdup(strchr(token, '=') + 1);
}

void load_session(const char* session_cookie) {
    User user;
    decode_user(session_cookie, &user);
    printf("Username: %s, Password: %s\n", user.username, user.password);
    free(user.username);
    free(user.password);
}

int main() {
    const char* session_cookie = "username=john_doe&password=secret";
    load_session(session_cookie);
    return 0;
}