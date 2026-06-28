#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *base_url;
    char *api_token;
} APIClient;

APIClient *create_api_client(const char *base_url, const char *env_var) {
    APIClient *client = (APIClient *)malloc(sizeof(APIClient));
    client->base_url = strdup(base_url);
    client->api_token = getenv(env_var);
    if (client->api_token == NULL) {
        fprintf(stderr, "Error: Environment variable not set\n");
        exit(EXIT_FAILURE);
    }
    return client;
}

void destroy_api_client(APIClient *client) {
    free(client->base_url);
    free(client);
}

int main() {
    const char *base_url = "https://api.example.com";
    const char *env_var = "API_TOKEN";
    APIClient *client = create_api_client(base_url, env_var);
    printf("API Client created with base URL: %s\n", client->base_url);
    destroy_api_client(client);
    return 0;
}