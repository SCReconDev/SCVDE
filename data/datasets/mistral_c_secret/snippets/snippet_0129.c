#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OAUTH_CLIENT_SECRET "fake_oauth_client_secret_1234567890"

void authenticate_user() {
    char auth_command[256];
    snprintf(auth_command, sizeof(auth_command), "curl -X POST https://auth.example.com/token -d 'client_id=client123&client_secret=%s'", OAUTH_CLIENT_SECRET);
    printf("Authenticating user: %s\n", auth_command);
    system(auth_command);
}

int main() {
    authenticate_user();
    return 0;
}