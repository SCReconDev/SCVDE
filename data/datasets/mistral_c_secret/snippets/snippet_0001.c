#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define API_TOKEN "fake_api_token_1234567890"

typedef struct {
    char *base_url;
    char *token;
} ApiClient;

ApiClient *create_client(const char *base_url) {
    ApiClient *client = (ApiClient *)malloc(sizeof(ApiClient));
    client->base_url = strdup(base_url);
    client->token = strdup(API_TOKEN);
    return client;
}

void destroy_client(ApiClient *client) {
    free(client->base_url);
    free(client->token);
    free(client);
}

int main() {
    ApiClient *client = create_client("https://api.example.com");
    printf("Client created with token: %s\n", client->token);
    destroy_client(client);
    return 0;
}