#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *api_token;
    char *base_url;
} ApiClient;

ApiClient *create_api_client(const char *base_url) {
    ApiClient *client = malloc(sizeof(ApiClient));
    if (client == NULL) {
        return NULL;
    }

    client->base_url = strdup(base_url);
    if (client->base_url == NULL) {
        free(client);
        return NULL;
    }

    client->api_token = getenv("API_TOKEN");
    if (client->api_token == NULL) {
        fprintf(stderr, "API_TOKEN environment variable not set\n");
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
        fprintf(stderr, "Failed to create API client\n");
        return 1;
    }

    printf("API client created with base URL: %s\n", client->base_url);
    printf("API token: %s\n", client->api_token);

    destroy_api_client(client);
    return 0;
}