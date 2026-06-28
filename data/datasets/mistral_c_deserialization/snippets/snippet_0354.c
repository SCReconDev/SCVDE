#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char username[50];
    char password[50];
} User;

void decode_user(const char* data, User* user) {
    char* decoded_data = malloc(strlen(data) + 1);
    strcpy(decoded_data, data);
    sscanf(decoded_data, "%49s %49s", user->username, user->password);
    free(decoded_data);
}

void load_session(const char* session_data) {
    User user;
    decode_user(session_data, &user);
    printf("Username: %s, Password: %s\n", user.username, user.password);
}

int main() {
    const char* session_data = "admin secret";
    load_session(session_data);
    return 0;
}