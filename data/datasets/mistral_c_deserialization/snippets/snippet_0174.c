#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* username;
    char* password;
} User;

void load_session(char* cookie) {
    User* user = (User*)malloc(sizeof(User));
    memcpy(user, cookie, sizeof(User));
    printf("User: %s\n", user->username);
    free(user);
}

int main() {
    char cookie[1024];
    fgets(cookie, sizeof(cookie), stdin);
    load_session(cookie);
    return 0;
}