#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define API_URL "https://api.example.com/v1/data"

typedef struct {
    char *api_token;
    char *base_url;
} ApiClient;

ApiClient* create_api_client(const char *api_token, const char *base_url) {
    ApiClient *client = (ApiClient*)malloc(sizeof(ApiClient));
    if (client == NULL) {
        return NULL;
    }

    client->api_token = strdup(api_token);
    if (client->api_token == NULL) {
        free(client);
        return NULL;
    }

    client->base_url = strdup(base_url);
    if (client->base_url == NULL) {
        free(client->api_token);
        free(client);
        return NULL;
    }

    return client;
}

void destroy_api_client(ApiClient *client) {
    if (client != NULL) {
        free(client->api_token);
        free(client->base_url);
        free(client);
    }
}

int fetch_data(ApiClient *client, const char *endpoint, char **response) {
    if (client == NULL || endpoint == NULL || response == NULL) {
        return -1;
    }

    char url[1024];
    snprintf(url, sizeof(url), "%s%s", client->base_url, endpoint);

    // Simulate API call
    printf("Fetching data from: %s\n", url);

    // In a real implementation, you would use a library like libcurl to make the HTTP request
    // and handle the response.

    // For this example, we'll just return a dummy response.
    *response = strdup("{\"data\": \"example data\"}");
    if (*response == NULL) {
        return -1;
    }

    return 0;
}

int main() {
    const char *api_token = getenv("API_TOKEN");
    if (api_token == NULL) {
        fprintf(stderr, "API_TOKEN environment variable not set.\n");
        return 1;
    }

    ApiClient *client = create_api_client(api_token, API_URL);
    if (client == NULL) {
        fprintf(stderr, "Failed to create API client.\n");
        return 1;
    }

    char *response = NULL;
    int result = fetch_data(client, "/items", &response);
    if (result != 0) {
        fprintf(stderr, "Failed to fetch data.\n");
        destroy_api_client(client);
        return 1;
    }

    printf("Response: %s\n", response);
    free(response);
    destroy_api_client(client);

    return 0;
}