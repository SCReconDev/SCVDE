#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define API_URL "https://api.example.com/v1"
#define API_TOKEN_ENV "API_TOKEN"

typedef struct {
    char *token;
    char *base_url;
} ApiClient;

ApiClient *create_api_client() {
    ApiClient *client = (ApiClient *)malloc(sizeof(ApiClient));
    if (client == NULL) {
        return NULL;
    }

    client->base_url = strdup(API_URL);
    if (client->base_url == NULL) {
        free(client);
        return NULL;
    }

    client->token = getenv(API_TOKEN_ENV);
    if (client->token == NULL) {
        fprintf(stderr, "API token not found in environment variables.\n");
        free(client->base_url);
        free(client);
        return NULL;
    }

    return client;
}

void destroy_api_client(ApiClient *client) {
    if (client != NULL) {
        if (client->base_url != NULL) {
            free(client->base_url);
        }
        free(client);
    }
}

int main() {
    ApiClient *client = create_api_client();
    if (client == NULL) {
        fprintf(stderr, "Failed to create API client.\n");
        return 1;
    }

    printf("API Client created successfully.\n");
    printf("Base URL: %s\n", client->base_url);
    printf("Token: %s\n", client->token);

    destroy_api_client(client);
    return 0;
}