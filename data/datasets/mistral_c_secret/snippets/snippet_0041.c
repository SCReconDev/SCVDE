#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define API_TOKEN "fake_api_token_1234567890"

typedef struct {
    char *base_url;
    char *token;
} ApiClient;

ApiClient* create_api_client(const char *base_url) {
    ApiClient *client = (ApiClient*)malloc(sizeof(ApiClient));
    client->base_url = strdup(base_url);
    client->token = strdup(API_TOKEN);
    return client;
}

void destroy_api_client(ApiClient *client) {
    free(client->base_url);
    free(client->token);
    free(client);
}

void make_api_request(ApiClient *client, const char *endpoint) {
    printf("Making API request to %s%s with token %s\n", client->base_url, endpoint, client->token);
}

int main() {
    ApiClient *client = create_api_client("https://api.example.com");
    make_api_request(client, "/data");
    destroy_api_client(client);
    return 0;
}