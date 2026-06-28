#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TOKEN_LENGTH 100

typedef struct {
    char token[MAX_TOKEN_LENGTH];
} ApiClient;

ApiClient* create_api_client() {
    ApiClient* client = (ApiClient*)malloc(sizeof(ApiClient));
    if (client == NULL) {
        return NULL;
    }

    const char* token_env = getenv("API_TOKEN");
    if (token_env == NULL) {
        fprintf(stderr, "API_TOKEN environment variable not set\n");
        free(client);
        return NULL;
    }

    strncpy(client->token, token_env, MAX_TOKEN_LENGTH - 1);
    client->token[MAX_TOKEN_LENGTH - 1] = '\0';

    return client;
}

void make_api_request(ApiClient* client, const char* endpoint) {
    printf("Making API request to %s with token: %s\n", endpoint, client->token);
}

void destroy_api_client(ApiClient* client) {
    if (client != NULL) {
        free(client);
    }
}

int main() {
    ApiClient* client = create_api_client();
    if (client == NULL) {
        return 1;
    }

    make_api_request(client, "/data");
    destroy_api_client(client);

    return 0;
}