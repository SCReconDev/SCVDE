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
    if (client == NULL) {
        return NULL;
    }

    client->url = strdup(API_URL);
    if (client->url == NULL) {
        free(client);
        return NULL;
    }

    client->token = getenv(API_TOKEN_ENV_VAR);
    if (client->token == NULL) {
        free(client->url);
        free(client);
        return NULL;
    }

    return client;
}

void destroy_api_client(ApiClient* client) {
    if (client != NULL) {
        if (client->url != NULL) {
            free(client->url);
        }
        free(client);
    }
}

int main() {
    ApiClient* client = create_api_client();
    if (client == NULL) {
        fprintf(stderr, "Failed to create API client\n");
        return 1;
    }

    printf("API Client created successfully\n");
    printf("URL: %s\n", client->url);
    printf("Token: %s\n", client->token);

    destroy_api_client(client);
    return 0;
}