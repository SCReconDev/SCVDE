#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OAUTH_CLIENT_SECRET "fake_oauth_client_secret_1234567890"

void authenticate_user(const char* username, const char* password) {
    printf("Authenticating user: %s\n", username);
    printf("Using OAuth client secret: %s\n", OAUTH_CLIENT_SECRET);
}

int main() {
    authenticate_user("user1", "password1");
    return 0;
}