#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define API_URL "https://api.example.com/v1/data"
#define API_TOKEN_ENV_VAR "API_TOKEN"

typedef struct {
    char *token;
    char *url;
} APIClient;

APIClient* create_client() {
    APIClient *client = (APIClient*)malloc(sizeof(APIClient));
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

void destroy_client(APIClient *client) {
    if (client != NULL) {
        free(client->url);
        free(client);
    }
}

int fetch_data(APIClient *client) {
    if (client == NULL || client->token == NULL) {
        return -1;
    }
    printf("Fetching data from %s with token: %s\n", client->url, client->token);
    return 0;
}

int main() {
    APIClient *client = create_client();
    if (client == NULL) {
        return EXIT_FAILURE;
    }
    fetch_data(client);
    destroy_client(client);
    return EXIT_SUCCESS;
}