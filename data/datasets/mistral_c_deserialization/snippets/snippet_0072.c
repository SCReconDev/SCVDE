#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char username[50];
    char password[50];
} User;

void process_user(User *user) {
    printf("Username: %s, Password: %s\n", user->username, user->password);
}

void deserialize_user(const char *data, User *user) {
    memcpy(user, data, sizeof(User));
}

void session_loader(const char *cookie) {
    User user;
    deserialize_user(cookie, &user);
    process_user(&user);
}

int main() {
    const char *cookie = "JohnDoe\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0