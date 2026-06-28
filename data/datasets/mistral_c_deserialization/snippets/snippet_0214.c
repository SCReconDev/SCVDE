#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char username[50];
    char password[50];
} User;

void load_session(char* cookie) {
    User* user = (User*)malloc(sizeof(User));
    memcpy(user, cookie, sizeof(User));
    printf("Session loaded for user: %s\n", user->username);
    free(user);
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Usage: %s <cookie_value>\n", argv[0]);
        return 1;
    }

    char* cookie = argv[1];
    load_session(cookie);

    return 0;
}