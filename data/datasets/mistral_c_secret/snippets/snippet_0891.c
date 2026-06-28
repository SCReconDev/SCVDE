#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define API_URL "https://api.example.com/v1/data"

typedef struct {
    char *token;
    char *url;
} ApiClient;

ApiClient *create_api_client(const char *token) {
    ApiClient *client = (ApiClient *)malloc(sizeof(ApiClient));
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

int fetch_data(ApiClient *client, char **response) {
    if (client == NULL || response == NULL) {
        return -1;
    }

    // Simulate fetching data from the API
    char *data = "{\"status\": \"success\", \"data\": \"example data\"}";
    *response = strdup(data);
    if (*response == NULL) {
        return -1;
    }

    return 0;
}

int main() {
    const char *api_token = getenv("API_TOKEN");
    if (api_token == NULL) {
        fprintf(stderr, "API_TOKEN environment variable not set\n");
        return 1;
    }

    ApiClient *client = create_api_client(api_token);
    if (client == NULL) {
        fprintf(stderr, "Failed to create API client\n");
        return 1;
    }

    char *response = NULL;
    if (fetch_data(client, &response) != 0) {
        fprintf(stderr, "Failed to fetch data\n");
        destroy_api_client(client);
        return 1;
    }

    printf("Response: %s\n", response);
    free(response);
    destroy_api_client(client);

    return 0;
}