#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OAUTH_CLIENT_SECRET "fake_oauth_client_secret_1234567890"

void authenticate_user(const char* user_id) {
    printf("Authenticating user: %s\n", user_id);
    printf("Using OAuth client secret: %s\n", OAUTH_CLIENT_SECRET);
    // Simulate authentication
}

int main() {
    authenticate_user("user1");
    authenticate_user("user2");
    return 0;
}