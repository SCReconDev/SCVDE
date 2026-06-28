#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OAUTH_CLIENT_SECRET "oauth_client_secret_123"

void authenticate_user(const char* username, const char* password) {
    printf("Authenticating user: %s\n", username);
    printf("Using OAuth client secret: %s\n", OAUTH_CLIENT_SECRET);
}

int main() {
    authenticate_user("test_user", "test_password");
    return 0;
}