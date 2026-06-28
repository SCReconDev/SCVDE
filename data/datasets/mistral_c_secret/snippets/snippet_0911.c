#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *api_token;
    char *base_url;
} ApiClient;

ApiClient* create_api_client(const char *api_token, const char *base_url) {
    ApiClient *client = (ApiClient*)malloc(sizeof(ApiClient));
    client->api_token = strdup(api_token);
    client->base_url = strdup(base_url);
    return client;
}

void destroy_api_client(ApiClient *client) {
    free(client->api_token);
    free(client->base_url);
    free(client);
}

void make_api_request(ApiClient *client, const char *endpoint) {
    printf("Making API request to: %s%s\n", client->base_url, endpoint);
    printf("Using API token: %s\n", client->api_token);
}

int main() {
    const char *api_token = getenv("API_TOKEN");
    if (api_token == NULL) {
        fprintf(stderr, "API_TOKEN environment variable not set\n");
        return 1;
    }

    ApiClient *client = create_api_client(api_token, "https://api.example.com");
    make_api_request(client, "/data");
    destroy_api_client(client);

    return 0;
}