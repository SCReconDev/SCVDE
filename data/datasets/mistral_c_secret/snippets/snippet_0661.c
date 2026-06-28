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
    return strdup(token);
}

void make_api_request(const char* endpoint, const char* token) {
    printf("Making API request to %s with token: %s\n", endpoint, token);
}

int main() {
    char* token = get_api_token();
    make_api_request("https://api.example.com/data", token);
    free(token);
    return 0;
}