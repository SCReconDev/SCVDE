#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OAUTH_CLIENT_SECRET "oauth_client_secret_123"

void authenticate_user() {
    char auth_url[256];
    snprintf(auth_url, sizeof(auth_url), "https://api.example.com/auth?client_secret=%s", OAUTH_CLIENT_SECRET);
    printf("Authenticating user: %s\n", auth_url);
}

int main() {
    authenticate_user();
    return 0;
}