#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define API_TOKEN "12345-ABCDE-67890-FGHIJ"

typedef struct {
    char *base_url;
    char *token;
} ApiClient;

ApiClient* create_api_client(const char *base_url) {
    ApiClient *client = (ApiClient*)malloc(sizeof(ApiClient));
    if (client == NULL) {
        return NULL;
    }

    client->base_url = strdup(base_url);
    if (client->base_url == NULL) {
        free(client);
        return NULL;
    }

    client->token = strdup(API_TOKEN);
    if (client->token == NULL) {
        free(client->base_url);
        free(client);
        return NULL;
    }

    return client;
}

void destroy_api_client(ApiClient *client) {
    if (client != NULL) {
        free(client->base_url);
        free(client->token);
        free(client);
    }
}

int main() {
    ApiClient *client = create_api_client("https://api.example.com");
    if (client == NULL) {
        fprintf(stderr, "Failed to create API client\n");
        return 1;
    }

    printf("API Client created with token: %s\n", client->token);

    destroy_api_client(client);
    return 0;
}