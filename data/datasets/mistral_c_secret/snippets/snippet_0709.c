#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *client_id;
    char *client_secret;
    char *redirect_uri;
} OAuthConfig;

OAuthConfig *create_oauth_config() {
    OAuthConfig *config = (OAuthConfig *)malloc(sizeof(OAuthConfig));
    if (config == NULL) {
        return NULL;
    }

    config->client_id = getenv("OAUTH_CLIENT_ID");
    if (config->client_id == NULL) {
        fprintf(stderr, "OAUTH_CLIENT_ID environment variable not set\n");
        free(config);
        return NULL;
    }

    config->client_secret = getenv("OAUTH_CLIENT_SECRET");
    if (config->client_secret == NULL) {
        fprintf(stderr, "OAUTH_CLIENT_SECRET environment variable not set\n");
        free(config);
        return NULL;
    }

    config->redirect_uri = getenv("OAUTH_REDIRECT_URI");
    if (config->redirect_uri == NULL) {
        fprintf(stderr, "OAUTH_REDIRECT_URI environment variable not set\n");
        free(config);
        return NULL;
    }

    return config;
}

void destroy_oauth_config(OAuthConfig *config) {
    if (config != NULL) {
        free(config);
    }
}

int main() {
    OAuthConfig *config = create_oauth_config();
    if (config == NULL) {
        return 1;
    }

    printf("OAuth Configuration:\n");
    printf("Client ID: %s\n", config->client_id);
    printf("Client Secret: %s\n", config->client_secret);
    printf("Redirect URI: %s\n", config->redirect_uri);

    destroy_oauth_config(config);
    return 0;
}