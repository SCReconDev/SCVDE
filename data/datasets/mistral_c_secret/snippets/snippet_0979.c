#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OAUTH_CLIENT_SECRET_ENV_VAR "OAUTH_CLIENT_SECRET"

typedef struct {
    char *auth_url;
    char *client_id;
    char *client_secret;
} ServiceClass;

ServiceClass* create_service_class(const char *auth_url, const char *client_id) {
    ServiceClass *service = (ServiceClass*)malloc(sizeof(ServiceClass));
    if (service == NULL) {
        return NULL;
    }

    service->auth_url = strdup(auth_url);
    service->client_id = strdup(client_id);

    if (service->auth_url == NULL || service->client_id == NULL) {
        free(service->auth_url);
        free(service->client_id);
        free(service);
        return NULL;
    }

    const char *secret = getenv(OAUTH_CLIENT_SECRET_ENV_VAR);
    if (secret == NULL) {
        fprintf(stderr, "Error: OAuth client secret not found in environment variables.\n");
        free(service->auth_url);
        free(service->client_id);
        free(service);
        return NULL;
    }

    service->client_secret = strdup(secret);
    if (service->client_secret == NULL) {
        free(service->auth_url);
        free(service->client_id);
        free(service);
        return NULL;
    }

    return service;
}

void destroy_service_class(ServiceClass *service) {
    if (service != NULL) {
        free(service->auth_url);
        free(service->client_id);
        free(service->client_secret);
        free(service);
    }
}

int main() {
    ServiceClass *service = create_service_class("https://auth.example.com", "my-client-id");
    if (service == NULL) {
        return EXIT_FAILURE;
    }

    printf("Service class created.\n");
    printf("Auth URL: %s\n", service->auth_url);
    printf("Client ID: %s\n", service->client_id);

    destroy_service_class(service);
    return EXIT_SUCCESS;
}