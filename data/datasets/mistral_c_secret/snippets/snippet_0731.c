#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define API_URL "https://api.example.com/v1/data"

typedef struct {
    char *api_token;
    char *base_url;
} ApiClient;

ApiClient *create_api_client(const char *api_token, const char *base_url) {
    ApiClient *client = (ApiClient *)malloc(sizeof(ApiClient));
    if (client == NULL) {
        return NULL;
    }

    client->api_token = strdup(api_token);
    client->base_url = strdup(base_url);

    if (client->api_token == NULL || client->base_url == NULL) {
        free(client->api_token);
        free(client->base_url);
        free(client);
        return NULL;
    }

    return client;
}

void destroy_api_client(ApiClient *client) {
    if (client != NULL) {
        free(client->api_token);
        free(client->base_url);
        free(client);
    }
}

int fetch_data(ApiClient *client, const char *endpoint) {
    if (client == NULL || endpoint == NULL) {
        return -1;
    }

    char url[256];
    snprintf(url, sizeof(url), "%s%s", client->base_url, endpoint);

    printf("Fetching data from: %s\n", url);
    printf("Using API token: %s\n", client->api_token);

    return 0;
}

int main() {
    const char *api_token = getenv("API_TOKEN");
    if (api_token == NULL) {
        fprintf(stderr, "API_TOKEN environment variable not set.\n");
        return 1;
    }

    ApiClient *client = create_api_client(api_token, API_URL);
    if (client == NULL) {
        fprintf(stderr, "Failed to create API client.\n");
        return 1;
    }

    fetch_data(client, "/users");

    destroy_api_client(client);

    return 0;
}