#include <stdio.h>

#define OAUTH_CLIENT_SECRET "fake_oauth_client_secret_1234567890"

void authenticate_user(const char* client_id) {
    printf("Authenticating user with client ID: %s\n", client_id);
    printf("Using client secret: %s\n", OAUTH_CLIENT_SECRET);
}

int main() {
    authenticate_user("fake_client_id_1234567890");
    return 0;
}