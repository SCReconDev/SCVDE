#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define API_URL "https://api.example.com/data"

typedef struct {
    char *token;
    char *url;
} ApiClient;

ApiClient* create_api_client(const char *token) {
    ApiClient *client = (ApiClient*)malloc(sizeof(ApiClient));
    if (client == NULL) {
        return NULL;
    }

    client->token = strdup(token);
    if (client->token == NULL) {
        free(client);
        return NULL;
    }

    client->url = strdup(API_URL);
    if (client->url == NULL) {
        free(client->token);
        free(client);
        return NULL;
    }

    return client;
}

void destroy_api_client(ApiClient *client) {
    if (client != NULL) {
        free(client->token);
        free(client->url);
        free(client);
    }
}

int fetch_data(ApiClient *client) {
    if (client == NULL || client->token == NULL || client->url == NULL) {
        return -1;
    }

    printf("Fetching data from %s with token %s\n", client->url, client->token);
    return 0;
}

int main() {
    const char *token = getenv("API_TOKEN");
    if (token == NULL) {
        fprintf(stderr, "API_TOKEN environment variable not set\n");
        return 1;
    }

    ApiClient *client = create_api_client(token);
    if (client == NULL) {
        fprintf(stderr, "Failed to create API client\n");
        return 1;
    }

    if (fetch_data(client) != 0) {
        fprintf(stderr, "Failed to fetch data\n");
        destroy_api_client(client);
        return 1;
    }

    destroy_api_client(client);
    return 0;
}