#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define API_TOKEN "fake_api_token_1234567890"

typedef struct {
    char *base_url;
    char *api_token;
} APIClient;

APIClient *create_api_client(const char *base_url) {
    APIClient *client = (APIClient *)malloc(sizeof(APIClient));
    if (client == NULL) {
        return NULL;
    }
    client->base_url = strdup(base_url);
    client->api_token = strdup(API_TOKEN);
    return client;
}

void destroy_api_client(APIClient *client) {
    if (client != NULL) {
        free(client->base_url);
        free(client->api_token);
        free(client);
    }
}

int main() {
    APIClient *client = create_api_client("https://api.example.com");
    if (client == NULL) {
        fprintf(stderr, "Failed to create API client\n");
        return EXIT_FAILURE;
    }

    printf("API Client created with token: %s\n", client->api_token);

    destroy_api_client(client);
    return EXIT_SUCCESS;
}