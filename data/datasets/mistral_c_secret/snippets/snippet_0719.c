#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OAUTH_CLIENT_SECRET_ENV_VAR "OAUTH_CLIENT_SECRET"

typedef struct {
    char *client_id;
    char *client_secret;
    char *redirect_uri;
} OAuthClient;

OAuthClient* create_oauth_client(const char *client_id, const char *redirect_uri) {
    OAuthClient *client = (OAuthClient*)malloc(sizeof(OAuthClient));
    if (client == NULL) {
        return NULL;
    }

    client->client_id = strdup(client_id);
    client->redirect_uri = strdup(redirect_uri);

    if (client->client_id == NULL || client->redirect_uri == NULL) {
        free(client->client_id);
        free(client->redirect_uri);
        free(client);
        return NULL;
    }

    char *client_secret = getenv(OAUTH_CLIENT_SECRET_ENV_VAR);
    if (client_secret == NULL) {
        fprintf(stderr, "OAuth client secret not found in environment variables\n");
        free(client->client_id);
        free(client->redirect_uri);
        free(client);
        return NULL;
    }

    client->client_secret = strdup(client_secret);
    if (client->client_secret == NULL) {
        free(client->client_id);
        free(client->redirect_uri);
        free(client);
        return NULL;
    }

    return client;
}

void destroy_oauth_client(OAuthClient *client) {
    if (client != NULL) {
        free(client->client_id);
        free(client->client_secret);
        free(client->redirect_uri);
        free(client);
    }
}

void print_oauth_client(OAuthClient *client) {
    if (client == NULL) {
        fprintf(stderr, "Invalid OAuth client\n");
        return;
    }

    printf("OAuth Client:\n");
    printf("Client ID: %s\n", client->client_id);
    printf("Client Secret: %s\n", client->client_secret);
    printf("Redirect URI: %s\n", client->redirect_uri);
}

int main() {
    OAuthClient *client = create_oauth_client("client_id", "https://example.com/callback");
    if (client == NULL) {
        fprintf(stderr, "Failed to create OAuth client\n");
        return 1;
    }

    print_oauth_client(client);
    destroy_oauth_client(client);

    return 0;
}