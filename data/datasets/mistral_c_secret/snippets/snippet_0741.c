#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define API_URL "https://api.example.com/v1/data"

typedef struct {
    char *api_token;
    char *base_url;
} ApiClient;

ApiClient* create_api_client(const char *api_token) {
    ApiClient *client = (ApiClient*)malloc(sizeof(ApiClient));
    if (client == NULL) {
        return NULL;
    }

    client->api_token = strdup(api_token);
    if (client->api_token == NULL) {
        free(client);
        return NULL;
    }

    client->base_url = strdup(API_URL);
    if (client->base_url == NULL) {
        free(client->api_token);
        free(client);
        return NULL;
    }

    return client;
}

void destroy_api_client(ApiClient *client) {
    if (client != NULL) {
        free(client->api_token);
        free(client->base_url);
        free(client);
    }
}

int main() {
    const char *api_token = getenv("API_TOKEN");
    if (api_token == NULL) {
        fprintf(stderr, "API_TOKEN environment variable not set\n");
        return 1;
    }

    ApiClient *client = create_api_client(api_token);
    if (client == NULL) {
        fprintf(stderr, "Failed to create API client\n");
        return 1;
    }

    printf("API Client created with token: %s\n", client->api_token);
    printf("Base URL: %s\n", client->base_url);

    destroy_api_client(client);

    return 0;
}