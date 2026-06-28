#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    if (service->client_id == NULL) {
        free(service);
        return NULL;
    }

    service->redirect_uri = strdup(redirect_uri);
    if (service->redirect_uri == NULL) {
        free(service->client_id);
        free(service);
        return NULL;
    }

    service->client_secret = getenv("CLIENT_SECRET");
    if (service->client_secret == NULL) {
        free(service->redirect_uri);
        free(service->client_id);
        free(service);
        return NULL;
    }

    return service;
}

void destroy_service_class(ServiceClass *service) {
    if (service != NULL) {
        if (service->client_secret != NULL) {
            free(service->client_secret);
        }
        if (service->redirect_uri != NULL) {
            free(service->redirect_uri);
        }
        if (service->client_id != NULL) {
            free(service->client_id);
        }
        free(service);
    }
}

int main() {
    ServiceClass *service = create_service_class("my-client-id", "https://example.com/callback");
    if (service == NULL) {
        fprintf(stderr, "Failed to create service class\n");
        return 1;
    }

    printf("Service class created with client ID: %s\n", service->client_id);
    printf("Service class created with redirect URI: %s\n", service->redirect_uri);
    printf("Service class created with client secret: %s\n", service->client_secret);

    destroy_service_class(service);
    return 0;
}