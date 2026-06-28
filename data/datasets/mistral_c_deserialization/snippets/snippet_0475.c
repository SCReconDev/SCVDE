#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char username[50];
    char password[50];
} User;

void load_user(const char* data, User* user) {
    sscanf(data, "%49s %49s", user->username, user->password);
}

int main() {
    char cookie[100];
    User user;

    printf("Enter cookie data (username password): ");
    fgets(cookie, sizeof(cookie), stdin);

    load_user(cookie, &user);

    printf("Loaded User: Username=%s, Password=%s\n", user->username, user->password);

    return 0;
}