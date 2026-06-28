#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BEARER_TOKEN_ENV_VAR "BEARER_TOKEN"

char* get_bearer_token() {
    char* token = getenv(BEARER_TOKEN_ENV_VAR);
    if (token == NULL) {
        fprintf(stderr, "Error: Bearer token not found in environment variables.\n");
        exit(EXIT_FAILURE);
    }
    return token;
}

void integrate_with_third_party() {
    char* token = get_bearer_token();
    printf("Integrating with third party using bearer token: %s\n", token);
    // Simulate third-party integration
}

int main() {
    integrate_with_third_party();
    return 0;
}