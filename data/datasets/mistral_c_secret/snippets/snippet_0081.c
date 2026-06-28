#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define API_TOKEN "fake_api_token_1234567890"

typedef struct {
    char *base_url;
    char *api_token;
} APIClient;

APIClient* create_api_client(const char *base_url) {
    APIClient *client = (APIClient*)malloc(sizeof(APIClient));
    client->base_url = strdup(base_url);
    client->api_token = strdup(API_TOKEN);
    return client;
}

void destroy_api_client(APIClient *client) {
    free(client->base_url);
    free(client->api_token);
    free(client);
}

void make_api_request(APIClient *client, const char *endpoint) {
    printf("Making request to %s%s with token %s\n", client->base_url, endpoint, client->api_token);
}

int main() {
    APIClient *client = create_api_client("https://api.example.com");
    make_api_request(client, "/v1/data");
    destroy_api_client(client);
    return 0;
}