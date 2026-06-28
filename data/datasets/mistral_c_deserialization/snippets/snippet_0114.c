#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* username;
    char* password;
} User;

void load_user_session(const char* session_data, User* user) {
    char* token = strtok((char*)session_data, "|");
    user->username = strdup(token);
    token = strtok(NULL, "|");
    user->password = strdup(token);
}

int main() {
    char* session_cookie = "admin|password123";
    User user;
    load_user_session(session_cookie, &user);
    printf("Username: %s, Password: %s\n", user.username, user.password);
    free(user.username);
    free(user.password);
    return 0;
}