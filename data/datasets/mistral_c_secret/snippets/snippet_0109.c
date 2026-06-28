#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OAUTH_CLIENT_SECRET "oauth_client_secret_123"

typedef struct {
    char *service_class;
    char *oauth_client_secret;
} ServiceClass;

ServiceClass* create_service_class(const char *service_class) {
    ServiceClass *service = (ServiceClass*)malloc(sizeof(ServiceClass));
    if (service == NULL) {
        return NULL;
    }

    service->service_class = strdup(service_class);
    if (service->service_class == NULL) {
        free(service);
        return NULL;
    }

    service->oauth_client_secret = strdup(OAUTH_CLIENT_SECRET);
    if (service->oauth_client_secret == NULL) {
        free(service->service_class);
        free(service);
        return NULL;
    }

    return service;
}

void destroy_service_class(ServiceClass *service) {
    if (service != NULL) {
        free(service->service_class);
        free(service->oauth_client_secret);
        free(service);
    }
}

int main() {
    ServiceClass *service = create_service_class("service_class_value");
    if (service == NULL) {
        fprintf(stderr, "Failed to create service class\n");
        return 1;
    }

    printf("Service class created with OAuth client secret: %s\n", service->oauth_client_secret);

    destroy_service_class(service);
    return 0;
}