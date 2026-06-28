#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define API_TOKEN_ENV_VAR "API_TOKEN"

typedef struct {
    char *base_url;
    char *api_token;
} ApiClient;

ApiClient* create_api_client(const char *base_url) {
    ApiClient *client = (ApiClient *)malloc(sizeof(ApiClient));
    if (client == NULL) {
        return NULL;
    }

    client->base_url = strdup(base_url);
    if (client->base_url == NULL) {
        free(client);
        return NULL;
    }

    client->api_token = getenv(API_TOKEN_ENV_VAR);
    if (client->api_token == NULL) {
        fprintf(stderr, "Error: API token not found in environment variables.\n");
        free(client->base_url);
        free(client);
        return NULL;
    }

    return client;
}

void destroy_api_client(ApiClient *client) {
    if (client != NULL) {
        free(client->base_url);
        free(client);
    }
}

int main() {
    ApiClient *client = create_api_client("https://api.example.com");
    if (client == NULL) {
        return 1;
    }

    printf("API Client created successfully.\n");
    printf("Base URL: %s\n", client->base_url);
    printf("API Token: %s\n", client->api_token);

    destroy_api_client(client);
    return 0;
}