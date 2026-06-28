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
    return strdup(token);
}

void integrate_with_third_party(const char* endpoint, const char* token) {
    printf("Integrating with third-party service at %s using token: %s\n", endpoint, token);
}

int main() {
    char* token = get_bearer_token();
    integrate_with_third_party("https://thirdparty.example.com/api", token);
    free(token);
    return 0;
}