#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OAUTH_CLIENT_SECRET "fake_oauth_client_secret_1234567890"

typedef struct {
    char *client_id;
    char *client_secret;
} OAuthConfig;

OAuthConfig *create_oauth_config(const char *client_id) {
    OAuthConfig *config = (OAuthConfig *)malloc(sizeof(OAuthConfig));
    config->client_id = strdup(client_id);
    config->client_secret = strdup(OAUTH_CLIENT_SECRET);
    return config;
}

void destroy_oauth_config(OAuthConfig *config) {
    free(config->client_id);
    free(config->client_secret);
    free(config);
}

int main() {
    OAuthConfig *config = create_oauth_config("client_123");
    printf("OAuth config created with client secret: %s\n", config->client_secret);
    destroy_oauth_config(config);
    return 0;
}