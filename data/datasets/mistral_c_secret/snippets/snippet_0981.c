#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define API_URL "https://api.example.com/v1"
#define API_TOKEN_ENV "API_TOKEN"

typedef struct {
    char *url;
    char *token;
} ApiClient;

ApiClient *create_api_client() {
    ApiClient *client = (ApiClient *)malloc(sizeof(ApiClient));
    if (client == NULL) {
        return NULL;
    }

    client->url = strdup(API_URL);
    if (client->url == NULL) {
        free(client);
        return NULL;
    }

    char *token = getenv(API_TOKEN_ENV);
    if (token == NULL) {
        free(client->url);
        free(client);
        return NULL;
    }

    client->token = strdup(token);
    if (client->token == NULL) {
        free(client->url);
        free(client);
        return NULL;
    }

    return client;
}

void destroy_api_client(ApiClient *client) {
    if (client != NULL) {
        free(client->url);
        free(client->token);
        free(client);
    }
}

int main() {
    ApiClient *client = create_api_client();
    if (client == NULL) {
        fprintf(stderr, "Failed to create API client\n");
        return 1;
    }

    printf("API Client created with URL: %s and Token: %s\n", client->url, client->token);

    destroy_api_client(client);
    return 0;
}