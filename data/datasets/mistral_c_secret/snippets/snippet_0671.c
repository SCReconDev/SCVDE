#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *api_token;
    char *base_url;
} ApiClient;

ApiClient* create_api_client() {
    ApiClient *client = (ApiClient*)malloc(sizeof(ApiClient));
    client->api_token = getenv("API_TOKEN");
    client->base_url = getenv("API_BASE_URL");
    if (client->api_token == NULL || client->base_url == NULL) {
        fprintf(stderr, "API_TOKEN and API_BASE_URL environment variables must be set.\n");
        free(client);
        return NULL;
    }
    return client;
}

void destroy_api_client(ApiClient *client) {
    if (client != NULL) {
        free(client);
    }
}

int main() {
    ApiClient *client = create_api_client();
    if (client == NULL) {
        return EXIT_FAILURE;
    }

    printf("API Token: %s\n", client->api_token);
    printf("Base URL: %s\n", client->base_url);

    destroy_api_client(client);
    return EXIT_SUCCESS;
}