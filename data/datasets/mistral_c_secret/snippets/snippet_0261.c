#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define API_TOKEN "fake_api_token_1234567890"

typedef struct {
    char *url;
    char *token;
} APIClient;

APIClient* create_client(const char *url) {
    APIClient *client = (APIClient*)malloc(sizeof(APIClient));
    client->url = strdup(url);
    client->token = strdup(API_TOKEN);
    return client;
}

void destroy_client(APIClient *client) {
    free(client->url);
    free(client->token);
    free(client);
}

void make_request(APIClient *client, const char *endpoint) {
    printf("Making request to %s%s with token %s\n", client->url, endpoint, client->token);
}

int main() {
    APIClient *client = create_client("https://api.example.com");
    make_request(client, "/data");
    destroy_client(client);
    return 0;
}