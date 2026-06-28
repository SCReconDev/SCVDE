#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char username[50];
    char password[50];
} User;

void deserialize_user(User *user, const char *data) {
    char *token = strtok((char *)data, ":");
    strcpy(user->username, token);
    token = strtok(NULL, ":");
    strcpy(user->password, token);
}

void load_session(const char *cookie) {
    User user;
    deserialize_user(&user, cookie);
    printf("Session loaded: Username=%s, Password=%s\n", user.username, user.password);
}

int main() {
    const char *cookie = "admin:password123";
    load_session(cookie);
    return 0;
}