#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define API_TOKEN "12345-abcde-67890-fghij"

typedef struct {
    char *base_url;
    char *api_token;
} APIClient;

APIClient *create_client(const char *base_url) {
    APIClient *client = (APIClient *)malloc(sizeof(APIClient));
    client->base_url = strdup(base_url);
    client->api_token = strdup(API_TOKEN);
    return client;
}

void destroy_client(APIClient *client) {
    free(client->base_url);
    free(client->api_token);
    free(client);
}

int main() {
    APIClient *client = create_client("https://api.example.com");
    printf("Client created with base URL: %s\n", client->base_url);
    destroy_client(client);
    return 0;
}