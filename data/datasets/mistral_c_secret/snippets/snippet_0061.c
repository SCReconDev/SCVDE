#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define API_TOKEN "12345-abcde-67890-fghij"

typedef struct {
    char *base_url;
    char *api_token;
} APIClient;

APIClient *create_api_client(const char *base_url) {
    APIClient *client = (APIClient *)malloc(sizeof(APIClient));
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
    char url[256];
    snprintf(url, sizeof(url), "%s%s", client->base_url, endpoint);
    printf("Making request to: %s with token: %s\n", url, client->api_token);
}

int main() {
    APIClient *client = create_api_client("https://api.example.com/v1/");
    make_api_request(client, "users");
    destroy_api_client(client);
    return 0;
}