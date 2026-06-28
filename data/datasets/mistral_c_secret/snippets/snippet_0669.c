#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OAUTH_CLIENT_SECRET_ENV_VAR "OAUTH_CLIENT_SECRET"

char* get_oauth_client_secret() {
    char* secret = getenv(OAUTH_CLIENT_SECRET_ENV_VAR);
    if (secret == NULL) {
        fprintf(stderr, "Error: OAuth client secret not found in environment variables.\n");
        exit(EXIT_FAILURE);
    }
    return strdup(secret);
}

void authenticate_with_oauth(const char* secret) {
    printf("Authenticating with OAuth using secret: %s\n", secret);
}

int main() {
    char* secret = get_oauth_client_secret();
    authenticate_with_oauth(secret);
    free(secret);
    return 0;
}