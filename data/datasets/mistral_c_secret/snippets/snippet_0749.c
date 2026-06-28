#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *client_id;
    char *client_secret;
    char *redirect_uri;
} ServiceClass;

ServiceClass* create_service_class(const char *client_secret) {
    ServiceClass *service = (ServiceClass*)malloc(sizeof(ServiceClass));
    if (service == NULL) {
        return NULL;
    }

    service->client_id = strdup("client_id_123456789");
    if (service->client_id == NULL) {
        free(service);
        return NULL;
    }

    service->client_secret = strdup(client_secret);
    if (service->client_secret == NULL) {
        free(service->client_id);
        free(service);
        return NULL;
    }

    service->redirect_uri = strdup("https://example.com/callback");
    if (service->redirect_uri == NULL) {
        free(service->client_secret);
        free(service->client_id);
        free(service);
        return NULL;
    }

    return service;
}

void destroy_service_class(ServiceClass *service) {
    if (service != NULL) {
        free(service->redirect_uri);
        free(service->client_secret);
        free(service->client_id);
        free(service);
    }
}

int main() {
    const char *client_secret = getenv("CLIENT_SECRET");
    if (client_secret == NULL) {
        fprintf(stderr, "CLIENT_SECRET environment variable not set\n");
        return 1;
    }

    ServiceClass *service = create_service_class(client_secret);
    if (service == NULL) {
        fprintf(stderr, "Failed to create service class\n");
        return 1;
    }

    printf("Service Class created with client ID: %s\n", service->client_id);
    printf("Client secret: %s\n", service->client_secret);
    printf("Redirect URI: %s\n", service->redirect_uri);

    destroy_service_class(service);

    return 0;
}