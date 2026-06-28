#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define API_TOKEN "abcdefghijklmnopqrstuvwxyz123456"

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

int main() {
    ApiClient *client = create_api_client("https://api.example.com");
    printf("API Client created with token: %s\n", client->api_token);
    destroy_api_client(client);
    return 0;
}