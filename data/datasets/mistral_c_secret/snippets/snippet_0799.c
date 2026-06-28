#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *client_id;
    char *client_secret;
    char *redirect_uri;
} ServiceClass;

ServiceClass *create_service_class(const char *client_id, const char *redirect_uri) {
    ServiceClass *service = malloc(sizeof(ServiceClass));
    if (service == NULL) {
        return NULL;
    }

    service->client_id = strdup(client_id);
    service->redirect_uri = strdup(redirect_uri);

    if (service->client_id == NULL || service->redirect_uri == NULL) {
        free(service->client_id);
        free(service->redirect_uri);
        free(service);
        return NULL;
    }

    service->client_secret = getenv("OAUTH_CLIENT_SECRET");
    if (service->client_secret == NULL) {
        fprintf(stderr, "OAUTH_CLIENT_SECRET environment variable not set\n");
        free(service->client_id);
        free(service->redirect_uri);
        free(service);
        return NULL;
    }

    return service;
}

void destroy_service_class(ServiceClass *service) {
    if (service != NULL) {
        free(service->client_id);
        free(service->redirect_uri);
        free(service);
    }
}

int main() {
    ServiceClass *service = create_service_class("123456789", "https://example.com/callback");
    if (service == NULL) {
        fprintf(stderr, "Failed to create service class\n");
        return 1;
    }

    printf("Service class created for client ID: %s\n", service->client_id);
    printf("Redirect URI: %s\n", service->redirect_uri);

    destroy_service_class(service);
    return 0;
}