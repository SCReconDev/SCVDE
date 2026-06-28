#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define API_TOKEN "fake_api_token_12345"

typedef struct {
    char *base_url;
    char *token;
} APIClient;

APIClient* create_api_client(const char *base_url) {
    APIClient *client = (APIClient*)malloc(sizeof(APIClient));
    client->base_url = strdup(base_url);
    client->token = strdup(API_TOKEN);
    return client;
}

void destroy_api_client(APIClient *client) {
    free(client->base_url);
    free(client->token);
    free(client);
}

void make_api_request(APIClient *client, const char *endpoint) {
    printf("Making request to %s%s with token %s\n", client->base_url, endpoint, client->token);
}

int main() {
    APIClient *client = create_api_client("https://api.example.com");
    make_api_request(client, "/data");
    destroy_api_client(client);
    return 0;
}