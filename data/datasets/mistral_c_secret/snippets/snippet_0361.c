#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define API_TOKEN "fake_api_token_1234567890"

typedef struct {
    char *api_url;
    char *api_token;
} ApiClient;

ApiClient *create_api_client(const char *url) {
    ApiClient *client = (ApiClient *)malloc(sizeof(ApiClient));
    if (client == NULL) {
        return NULL;
    }

    client->api_url = strdup(url);
    client->api_token = strdup(API_TOKEN);

    return client;
}

void destroy_api_client(ApiClient *client) {
    if (client != NULL) {
        free(client->api_url);
        free(client->api_token);
        free(client);
    }
}

int main() {
    ApiClient *client = create_api_client("https://api.example.com");
    if (client == NULL) {
        fprintf(stderr, "Failed to create API client\n");
        return 1;
    }

    printf("API Client created with URL: %s\n", client->api_url);
    printf("API Token: %s\n", client->api_token);

    destroy_api_client(client);
    return 0;
}