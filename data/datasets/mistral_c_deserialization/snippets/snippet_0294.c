#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* username;
    char* password;
} User;

void load_session(const char* cookie) {
    User* user = (User*)malloc(sizeof(User));
    memcpy(user, cookie, sizeof(User));

    printf("User: %s, Password: %s\n", user->username, user->password);
    free(user);
}

int main() {
    char* session_cookie = "Alice\0password123";
    load_session(session_cookie);
    return 0;
}