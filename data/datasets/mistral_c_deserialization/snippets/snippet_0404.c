#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* username;
    char* password;
} User;

void decode_user(const char* cookie, User* user) {
    char* token = strtok((char*)cookie, "&");
    while (token != NULL) {
        char* key = strtok(token, "=");
        char* value = strtok(NULL, "=");
        if (strcmp(key, "username") == 0) {
            user->username = strdup(value);
        } else if (strcmp(key, "password") == 0) {
            user->password = strdup(value);
        }
        token = strtok(NULL, "&");
    }
}

int main() {
    char* session_cookie = "username=admin&password=secret";
    User user;
    decode_user(session_cookie, &user);
    printf("Username: %s, Password: %s\n", user.username, user.password);
    free(user.username);
    free(user.password);
    return 0;
}