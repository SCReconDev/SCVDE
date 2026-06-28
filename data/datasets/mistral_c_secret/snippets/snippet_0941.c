#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define API_TOKEN_ENV_VAR "API_TOKEN"

typedef struct {
    char *base_url;
    char *api_token;
} APIClient;

APIClient* create_api_client(const char *base_url) {
    APIClient *client = (APIClient*)malloc(sizeof(APIClient));
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
        free(client->base_url);
        free(client);
        return NULL;
    }

    return client;
}

void destroy_api_client(APIClient *client) {
    if (client != NULL) {
        free(client->base_url);
        free(client);
    }
}

int main() {
    const char *base_url = "https://api.example.com";
    APIClient *client = create_api_client(base_url);

    if (client == NULL) {
        fprintf(stderr, "Failed to create API client\n");
        return 1;
    }

    printf("API Client created with base URL: %s\n", client->base_url);
    printf("API Token: %s\n", client->api_token);

    destroy_api_client(client);
    return 0;
}