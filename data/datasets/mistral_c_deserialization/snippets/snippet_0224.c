#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char username[50];
    char password[50];
} User;

void load_session(const char* cookie, User* user) {
    char* data = strdup(cookie);
    char* token = strtok(data, "&");
    while (token != NULL) {
        char* key = strtok(NULL, "=");
        char* value = strtok(NULL, "&");
        if (strcmp(key, "username") == 0) {
            strcpy(user->username, value);
        } else if (strcmp(key, "password") == 0) {
            strcpy(user->password, value);
        }
        token = strtok(NULL, "&");
    }
    free(data);
}

int main() {
    char* cookie = "username=admin&password=secret";
    User user;
    load_session(cookie, &user);
    printf("Username: %s, Password: %s\n", user.username, user.password);
    return 0;
}