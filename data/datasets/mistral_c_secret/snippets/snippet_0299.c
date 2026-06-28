#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OAUTH_CLIENT_SECRET "oauth_client_secret_123"

typedef struct {
    char *client_id;
    char *client_secret;
    char *redirect_uri;
} ServiceClass;

ServiceClass* create_service_class(const char *client_id, const char *redirect_uri) {
    ServiceClass *service = (ServiceClass*)malloc(sizeof(ServiceClass));
    if (service == NULL) {
        return NULL;
    }

    service->client_id = strdup(client_id);
    service->client_secret = strdup(OAUTH_CLIENT_SECRET);
    service->redirect_uri = strdup(redirect_uri);

    return service;
}

void destroy_service_class(ServiceClass *service) {
    if (service != NULL) {
        free(service->client_id);
        free(service->client_secret);
        free(service->redirect_uri);
        free(service);
    }
}

int main() {
    ServiceClass *service = create_service_class("client123", "https://example.com/callback");
    if (service == NULL) {
        fprintf(stderr, "Failed to create service class\n");
        return 1;
    }

    printf("Service Class created with client secret: %s\n", service->client_secret);

    destroy_service_class(service);
    return 0;
}