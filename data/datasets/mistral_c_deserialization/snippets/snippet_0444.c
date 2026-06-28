#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char username[50];
    char password[50];
} User;

void load_session(const char* cookie) {
    User* user = (User*)malloc(sizeof(User));
    memcpy(user, cookie, sizeof(User));
    printf("Username: %s, Password: %s\n", user->username, user->password);
    free(user);
}

int main() {
    char cookie[sizeof(User)];
    memset(cookie, 0, sizeof(cookie));
    strcpy(cookie, "admin");
    strcpy(cookie + 50, "secret");

    load_session(cookie);
    return 0;
}