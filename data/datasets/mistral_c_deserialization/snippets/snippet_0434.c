#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* username;
    char* password;
} User;

void authenticate(User* user) {
    printf("Authenticating user: %s\n", user->username);
}

int main() {
    char* session_data = "{\"username\":\"admin\",\"password\":\"admin123\"}";
    User* user = (User*)malloc(sizeof(User));
    memcpy(user, session_data, sizeof(User));
    authenticate(user);
    free(user);
    return 0;
}