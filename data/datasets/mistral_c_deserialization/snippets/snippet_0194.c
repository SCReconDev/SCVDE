#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* username;
    char* password;
} User;

void load_session(const char* cookie) {
    User* user = (User*)cookie;
    printf("Username: %s, Password: %s\n", user->username, user->password);
}

int main() {
    const char* session_cookie = "{\"username\":\"admin\",\"password\":\"secret\"}";
    load_session(session_cookie);
    return 0;
}