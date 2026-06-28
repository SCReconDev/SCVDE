#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OAUTH_SECRET "fake_oauth_secret_1234567890"

void authenticate_user(const char* user_id) {
    printf("Authenticating user %s with OAuth secret %s\n", user_id, OAUTH_SECRET);
}

int main() {
    authenticate_user("user_123");
    authenticate_user("user_456");
    return 0;
}