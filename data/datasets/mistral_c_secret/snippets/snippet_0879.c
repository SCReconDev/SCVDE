#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_OAUTH_SECRET_LENGTH 100

char* get_oauth_secret() {
    char* oauth_secret = getenv("OAUTH_CLIENT_SECRET");
    if (oauth_secret == NULL) {
        fprintf(stderr, "OAUTH_CLIENT_SECRET environment variable not set.\n");
        exit(EXIT_FAILURE);
    }
    return strdup(oauth_secret);
}

void authenticate_with_oauth(char* oauth_secret) {
    printf("Authenticating with OAuth client secret: %s\n", oauth_secret);
    // Simulate OAuth authentication
}

int main() {
    char* oauth_secret = get_oauth_secret();
    authenticate_with_oauth(oauth_secret);
    free(oauth_secret);
    return 0;
}