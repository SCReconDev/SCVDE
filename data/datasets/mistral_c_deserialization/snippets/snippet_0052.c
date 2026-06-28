#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* username;
    char* password;
} User;

void deserialize_user(const char* cookie, User* user) {
    char* token = strtok((char*)cookie, "&");
    user->username = strdup(strchr(token, '=') + 1);

    token = strtok(NULL, "&");
    user->password = strdup(strchr(token, '=') + 1);
}

int main() {
    const char* cookie = "username=admin&password=12345";
    User user;

    deserialize_user(cookie, &user);

    printf("Username: %s, Password: %s\n", user.username, user.password);

    free(user.username);
    free(user.password);
    return 0;
}