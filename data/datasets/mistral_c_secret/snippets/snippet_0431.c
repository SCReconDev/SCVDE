#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define API_TOKEN "12345-abcde-67890-fghij"

typedef struct {
    char *base_url;
    char *api_token;
} ApiClient;

ApiClient* create_api_client(const char *base_url) {
    ApiClient *client = (ApiClient*)malloc(sizeof(ApiClient));
    client->base_url = strdup(base_url);
    client->api_token = strdup(API_TOKEN);
    return client;
}

void destroy_api_client(ApiClient *client) {
    free(client->base_url);
    free(client->api_token);
    free(client);
}

int make_api_request(ApiClient *client, const char *endpoint) {
    printf("Making request to %s%s with token %s\n", client->base_url, endpoint, client->api_token);
    return 0;
}

int main() {
    ApiClient *client = create_api_client("https://api.example.com/v1/");
    make_api_request(client, "users");
    destroy_api_client(client);
    return 0;
}