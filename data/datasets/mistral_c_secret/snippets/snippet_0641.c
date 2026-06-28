#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define API_TOKEN_ENV_VAR "API_TOKEN"

char* get_api_token() {
    char* token = getenv(API_TOKEN_ENV_VAR);
    if (token == NULL) {
        fprintf(stderr, "Error: API token not found in environment variables.\n");
        exit(EXIT_FAILURE);
    }
    return token;
}

void make_api_request() {
    char* token = get_api_token();
    printf("Making API request with token: %s\n", token);
    // Simulate API request
}

int main() {
    make_api_request();
    return 0;
}