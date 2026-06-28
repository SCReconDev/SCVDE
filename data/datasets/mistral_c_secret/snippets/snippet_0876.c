#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BEARER_TOKEN_LENGTH 100

char* get_bearer_token() {
    char* bearer_token = getenv("BEARER_TOKEN");
    if (bearer_token == NULL) {
        fprintf(stderr, "BEARER_TOKEN environment variable not set.\n");
        exit(EXIT_FAILURE);
    }
    return strdup(bearer_token);
}

void integrate_with_third_party(char* bearer_token) {
    printf("Integrating with third-party service with bearer token: %s\n", bearer_token);
    // Simulate third-party integration
}

int main() {
    char* bearer_token = get_bearer_token();
    integrate_with_third_party(bearer_token);
    free(bearer_token);
    return 0;
}