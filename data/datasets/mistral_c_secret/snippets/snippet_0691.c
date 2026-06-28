#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *api_token;
    char *base_url;
} APIClient;

APIClient *create_api_client(const char *base_url) {
    APIClient *client = malloc(sizeof(APIClient));
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
        free(client->base_url);
        free(client);
        return NULL;
    }

    return client;
}

void destroy_api_client(APIClient *client) {
    if (client != NULL) {
        if (client->base_url != NULL) {
            free(client->base_url);
        }
        free(client);
    }
}

int main() {
    APIClient *client = create_api_client("https://api.example.com");
    if (client == NULL) {
        fprintf(stderr, "Failed to create API client\n");
        return 1;
    }

    printf("API Client created with token: %s\n", client->api_token);

    destroy_api_client(client);
    return 0;
}