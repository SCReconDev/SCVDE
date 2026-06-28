#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define API_TOKEN_ENV_VAR "API_TOKEN"

typedef struct {
    char *base_url;
    char *api_token;
} ApiClient;

ApiClient *create_api_client(const char *base_url) {
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
        fprintf(stderr, "API token not found in environment variables.\n");
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
    const char *base_url = "https://api.example.com";
    ApiClient *client = create_api_client(base_url);

    if (client != NULL) {
        printf("API Client created successfully.\n");
        destroy_api_client(client);
    } else {
        printf("Failed to create API Client.\n");
    }

    return 0;
}