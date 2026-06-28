#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* username;
    char* password;
} User;

void load_user(User* user, const char* data) {
    char* token = strtok((char*)data, ":");
    user->username = strdup(token);
    token = strtok(NULL, ":");
    user->password = strdup(token);
}

int main() {
    char* session_data = "admin:password123";
    User user;
    load_user(&user, session_data);
    printf("Username: %s, Password: %s\n", user.username, user.password);
    free(user.username);
    free(user.password);
    return 0;
}