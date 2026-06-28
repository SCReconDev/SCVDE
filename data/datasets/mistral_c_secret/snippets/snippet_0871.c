#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TOKEN_LENGTH 100

char* get_api_token() {
    char* token = getenv("API_TOKEN");
    if (token == NULL) {
        fprintf(stderr, "API_TOKEN environment variable not set.\n");
        exit(EXIT_FAILURE);
    }
    return strdup(token);
}

void make_api_request(char* token) {
    printf("Making API request with token: %s\n", token);
    // Simulate API request
}

int main() {
    char* token = get_api_token();
    make_api_request(token);
    free(token);
    return 0;
}