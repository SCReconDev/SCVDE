#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BUFFER_SIZE 1024

typedef struct {
    char *api_token;
    char *base_url;
} APIClient;

APIClient* create_api_client() {
    APIClient *client = (APIClient*)malloc(sizeof(APIClient));
    if (client == NULL) {
        return NULL;
    }

    char *token = getenv("API_TOKEN");
    if (token == NULL) {
        fprintf(stderr, "API_TOKEN environment variable not set\n");
        free(client);
        return NULL;
    }

    client->api_token = strdup(token);
    if (client->api_token == NULL) {
        free(client);
        return NULL;
    }

    char *url = getenv("API_BASE_URL");
    if (url == NULL) {
        fprintf(stderr, "API_BASE_URL environment variable not set\n");
        free(client->api_token);
        free(client);
        return NULL;
    }

    client->base_url = strdup(url);
    if (client->base_url == NULL) {
        free(client->api_token);
        free(client);
        return NULL;
    }

    return client;
}

void destroy_api_client(APIClient *client) {
    if (client != NULL) {
        if (client->api_token != NULL) {
            free(client->api_token);
        }
        if (client->base_url != NULL) {
            free(client->base_url);
        }
        free(client);
    }
}

int make_api_request(APIClient *client, const char *endpoint, char *response_buffer, size_t buffer_size) {
    if (client == NULL || endpoint == NULL || response_buffer == NULL || buffer_size == 0) {
        return -1;
    }

    char url[MAX_BUFFER_SIZE];
    snprintf(url, MAX_BUFFER_SIZE, "%s%s", client->base_url, endpoint);

    // Simulate making an API request
    snprintf(response_buffer, buffer_size, "Response from %s", url);

    return 0;
}

int main() {
    APIClient *client = create_api_client();
    if (client == NULL) {
        return 1;
    }

    char response[MAX_BUFFER_SIZE];
    if (make_api_request(client, "/data", response, MAX_BUFFER_SIZE) != 0) {
        fprintf(stderr, "Failed to make API request\n");
        destroy_api_client(client);
        return 1;
    }

    printf("API Response: %s\n", response);

    destroy_api_client(client);
    return 0;
}