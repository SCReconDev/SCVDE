#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char username[256];
    char password[256];
} User;

void deserialize_user(User *user, const char *data) {
    sscanf(data, "%255[^;];%255[^;]", user->username, user->password);
}

void load_session(const char *cookie) {
    User user;
    deserialize_user(&user, cookie);
    printf("User: %s, Password: %s\n", user.username, user.password);
}

int main() {
    char cookie[512];
    printf("Enter session cookie: ");
    fgets(cookie, sizeof(cookie), stdin);
    load_session(cookie);
    return 0;
}