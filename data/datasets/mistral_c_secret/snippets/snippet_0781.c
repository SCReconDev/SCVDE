#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *base_url;
    char *api_token;
} APIClient;

APIClient *create_client(const char *base_url) {
    APIClient *client = (APIClient *)malloc(sizeof(APIClient));
    if (client == NULL) {
        return NULL;
    }
    client->base_url = strdup(base_url);
    client->api_token = getenv("API_TOKEN");
    if (client->api_token == NULL) {
        free(client->base_url);
        free(client);
        return NULL;
    }
    return client;
}

void destroy_client(APIClient *client) {
    if (client != NULL) {
        free(client->base_url);
        free(client);
    }
}

int main() {
    APIClient *client = create_client("https://api.example.com");
    if (client == NULL) {
        fprintf(stderr, "Failed to create client\n");
        return 1;
    }
    printf("Client created with token: %s\n", client->api_token);
    destroy_client(client);
    return 0;
}