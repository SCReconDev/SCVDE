#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define API_TOKEN "fake_api_token_1234567890"

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

    client->api_token = strdup(API_TOKEN);
    if (client->api_token == NULL) {
        free(client->base_url);
        free(client);
        return NULL;
    }

    return client;
}

void destroy_api_client(ApiClient *client) {
    if (client != NULL) {
        free(client->base_url);
        free(client->api_token);
        free(client);
    }
}

int main() {
    ApiClient *client = create_api_client("https://api.example.com");
    if (client == NULL) {
        fprintf(stderr, "Failed to create API client\n");
        return EXIT_FAILURE;
    }

    printf("API Client created with base URL: %s\n", client->base_url);
    printf("API Token: %s\n", client->api_token);

    destroy_api_client(client);
    return EXIT_SUCCESS;
}