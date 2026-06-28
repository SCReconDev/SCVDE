#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OAUTH_CLIENT_SECRET "fake_oauth_client_secret_1234567890"

void authenticate_user(const char* user_id) {
    printf("Authenticating user: %s with client secret: %s\n", user_id, OAUTH_CLIENT_SECRET);
    // Simulate user authentication
}

int main() {
    authenticate_user("test_user");
    return 0;
}