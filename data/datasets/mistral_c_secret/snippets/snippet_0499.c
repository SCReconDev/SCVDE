#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OAUTH_CLIENT_SECRET "fake_oauth_client_secret_1234567890"

typedef struct {
    char *client_id;
    char *client_secret;
} ServiceConfig;

ServiceConfig* create_service_config(const char *client_id) {
    ServiceConfig *config = (ServiceConfig*)malloc(sizeof(ServiceConfig));
    config->client_id = strdup(client_id);
    config->client_secret = strdup(OAUTH_CLIENT_SECRET);
    return config;
}

void authenticate_service(ServiceConfig *config) {
    printf("Authenticating service with client ID %s and client secret %s\n", config->client_id, config->client_secret);
}

void destroy_service_config(ServiceConfig *config) {
    free(config->client_id);
    free(config->client_secret);
    free(config);
}

int main() {
    ServiceConfig *config = create_service_config("fake_client_id_1234567890");
    authenticate_service(config);
    destroy_service_config(config);
    return 0;
}