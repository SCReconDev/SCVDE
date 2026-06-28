#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define API_URL "https://api.example.com/v1/data"
#define API_TOKEN_ENV_VAR "API_TOKEN"

typedef struct {
    char* token;
    char* url;
} ApiClient;

ApiClient* create_api_client() {
    ApiClient* client = (ApiClient*)malloc(sizeof(ApiClient));
    client->url = strdup(API_URL);
    client->token = getenv(API_TOKEN_ENV_VAR);
    if (client->token == NULL) {
        fprintf(stderr, "Error: API token not found in environment variables.\n");
        free(client->url);
        free(client);
        return NULL;
    }
    return client;
}

void destroy_api_client(ApiClient* client) {
    if (client != NULL) {
        free(client->url);
        free(client);
    }
}

int fetch_data(ApiClient* client) {
    if (client == NULL || client->token == NULL) {
        return -1;
    }
    printf("Fetching data from %s with token %s...\n", client->url, client->token);
    // Actual API call would go here
    return 0;
}

int main() {
    ApiClient* client = create_api_client();
    if (client == NULL) {
        return 1;
    }
    fetch_data(client);
    destroy_api_client(client);
    return 0;
}