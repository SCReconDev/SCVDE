#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BUFFER_SIZE 1024

typedef struct {
    char *base_url;
    char *api_token;
} ApiClient;

ApiClient* create_api_client(const char *base_url, const char *api_token) {
    ApiClient *client = (ApiClient *)malloc(sizeof(ApiClient));
    if (client == NULL) {
        return NULL;
    }

    client->base_url = strdup(base_url);
    client->api_token = strdup(api_token);

    if (client->base_url == NULL || client->api_token == NULL) {
        free(client->base_url);
        free(client->api_token);
        free(client);
        return NULL;
    }

    return client;
}

void destroy_api_client(ApiClient *client) {
    if (client != NULL) {
        free(client->base_url);
        free(client->api_token);
        free(client);
    }
}

int make_api_request(ApiClient *client, const char *endpoint, char *response_buffer, size_t buffer_size) {
    if (client == NULL || endpoint == NULL || response_buffer == NULL || buffer_size < 1) {
        return -1;
    }

    char url[MAX_BUFFER_SIZE];
    snprintf(url, sizeof(url), "%s%s", client->base_url, endpoint);

    char command[MAX_BUFFER_SIZE];
    snprintf(command, sizeof(command), "curl -H \"Authorization: Bearer %s\" %s", client->api_token, url);

    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        return -1;
    }

    size_t bytes_read = fread(response_buffer, 1, buffer_size - 1, fp);
    response_buffer[bytes_read] = '\0';

    pclose(fp);

    return 0;
}

int main() {
    const char *base_url = "https://api.example.com";
    const char *api_token_env = getenv("API_TOKEN");

    if (api_token_env == NULL) {
        fprintf(stderr, "API_TOKEN environment variable not set.\n");
        return 1;
    }

    ApiClient *client = create_api_client(base_url, api_token_env);
    if (client == NULL) {
        fprintf(stderr, "Failed to create API client.\n");
        return 1;
    }

    char response_buffer[MAX_BUFFER_SIZE];
    if (make_api_request(client, "/data", response_buffer, sizeof(response_buffer)) != 0) {
        fprintf(stderr, "Failed to make API request.\n");
        destroy_api_client(client);
        return 1;
    }

    printf("API Response: %s\n", response_buffer);

    destroy_api_client(client);

    return 0;
}