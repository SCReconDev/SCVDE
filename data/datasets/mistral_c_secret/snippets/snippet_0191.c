#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define API_TOKEN "fake_api_token_1234567890"

typedef struct {
    char *base_url;
    char *api_token;
} APIClient;

APIClient* create_client(const char *base_url) {
    APIClient *client = (APIClient*)malloc(sizeof(APIClient));
    client->base_url = strdup(base_url);
    client->api_token = strdup(API_TOKEN);
    return client;
}

void destroy_client(APIClient *client) {
    free(client->base_url);
    free(client->api_token);
    free(client);
}

void make_request(APIClient *client, const char *endpoint) {
    char url[256];
    snprintf(url, sizeof(url), "%s%s", client->base_url, endpoint);
    printf("Making request to: %s\n", url);
    printf("Using API token: %s\n", client->api_token);
}

int main() {
    APIClient *client = create_client("https://api.example.com/");
    make_request(client, "v1/data");
    destroy_client(client);
    return 0;
}