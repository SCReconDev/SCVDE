#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *client_id;
    char *client_secret;
    char *redirect_uri;
} OAuthConfig;

OAuthConfig* create_oauth_config(const char *client_id, const char *client_secret, const char *redirect_uri) {
    OAuthConfig *config = (OAuthConfig*)malloc(sizeof(OAuthConfig));
    config->client_id = strdup(client_id);
    config->client_secret = strdup(client_secret);
    config->redirect_uri = strdup(redirect_uri);
    return config;
}

void destroy_oauth_config(OAuthConfig *config) {
    free(config->client_id);
    free(config->client_secret);
    free(config->redirect_uri);
    free(config);
}

void oauth_flow(OAuthConfig *config) {
    printf("Starting OAuth flow\n");
    printf("Client ID: %s\n", config->client_id);
    printf("Client Secret: %s\n", config->client_secret);
    printf("Redirect URI: %s\n", config->redirect_uri);
}

int main() {
    const char *oauth_client_secret = getenv("OAUTH_CLIENT_SECRET");
    if (oauth_client_secret == NULL) {
        fprintf(stderr, "OAUTH_CLIENT_SECRET environment variable not set\n");
        return 1;
    }

    OAuthConfig *config = create_oauth_config("client_id_example", oauth_client_secret, "https://example.com/callback");
    oauth_flow(config);
    destroy_oauth_config(config);

    return 0;
}