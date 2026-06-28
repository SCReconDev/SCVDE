#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char username[50];
    char password[50];
} User;

void decode_user(User *user, const char *data) {
    sscanf(data, "%49s %49s", user->username, user->password);
}

void load_session(const char *cookie) {
    User user;
    decode_user(&user, cookie);
    printf("Username: %s, Password: %s\n", user.username, user.password);
}

int main() {
    char cookie[100];
    printf("Enter session cookie: ");
    fgets(cookie, sizeof(cookie), stdin);
    load_session(cookie);
    return 0;
}