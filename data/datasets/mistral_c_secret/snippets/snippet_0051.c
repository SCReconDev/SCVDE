#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define API_TOKEN "fake_api_token_1234567890"

typedef struct {
    char *base_url;
    char *token;
} ApiClient;

ApiClient *create_api_client(const char *base_url) {
    ApiClient *client = (ApiClient *)malloc(sizeof(ApiClient));
    if (client == NULL) {
        return NULL;
    }
    client->base_url = strdup(base_url);
    client->token = strdup(API_TOKEN);
    return client;
}

void destroy_api_client(ApiClient *client) {
    if (client != NULL) {
        free(client->base_url);
        free(client->token);
        free(client);
    }
}

int make_api_request(ApiClient *client, const char *endpoint) {
    if (client == NULL || endpoint == NULL) {
        return -1;
    }
    printf("Making request to %s%s with token %s\n", client->base_url, endpoint, client->token);
    return 0;
}

int main() {
    ApiClient *client = create_api_client("https://api.example.com");
    if (client == NULL) {
        fprintf(stderr, "Failed to create API client\n");
        return 1;
    }
    make_api_request(client, "/data");
    destroy_api_client(client);
    return 0;
}