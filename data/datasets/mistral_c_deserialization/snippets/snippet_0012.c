#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* username;
    char* password;
} User;

void deserialize_user(User* user, const char* data) {
    char* token = strtok((char*)data, ":");
    user->username = strdup(token);
    token = strtok(NULL, ":");
    user->password = strdup(token);
}

void load_session(const char* cookie) {
    User user;
    deserialize_user(&user, cookie);
    printf("Username: %s, Password: %s\n", user.username, user.password);
    free(user.username);
    free(user.password);
}

int main() {
    const char* cookie = "admin:password123";
    load_session(cookie);
    return 0;
}