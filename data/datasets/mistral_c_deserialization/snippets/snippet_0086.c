#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char username[50];
    char password[50];
} User;

void load_session(User *user, const char *cookie) {
    char *token = strtok((char *)cookie, ":");
    strcpy(user->username, token);
    token = strtok(NULL, ":");
    strcpy(user->password, token);
}

int main() {
    char cookie[100];
    User user;

    printf("Enter session cookie: ");
    fgets(cookie, sizeof(cookie), stdin);

    load_session(&user, cookie);

    printf("Session User: Username=%s, Password=%s\n", user.username, user.password);

    return 0;
}