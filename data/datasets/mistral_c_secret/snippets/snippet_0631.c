#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define API_URL "https://api.example.com/v1/resource"

typedef struct {
    char *token;
    char *url;
} APIClient;

APIClient* create_client() {
    APIClient *client = (APIClient*)malloc(sizeof(APIClient));
    if (client == NULL) {
        return NULL;
    }

    client->token = getenv("API_TOKEN");
    if (client->token == NULL) {
        fprintf(stderr, "API_TOKEN environment variable not set.\n");
        free(client);
        return NULL;
    }

    client->url = strdup(API_URL);
    if (client->url == NULL) {
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

int main() {
    APIClient *client = create_client();
    if (client == NULL) {
        return 1;
    }

    printf("API Client created with token: %s\n", client->token);
    destroy_client(client);
    return 0;
}