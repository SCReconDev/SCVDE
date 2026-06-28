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
    printf("User: %s, Password: %s\n", user->username, user->password);
    free(user);
}

int main() {
    char cookie[100];
    printf("Enter cookie: ");
    fgets(cookie, sizeof(cookie), stdin);
    load_session(cookie);
    return 0;
}