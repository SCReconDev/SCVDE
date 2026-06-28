#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OAUTH_CLIENT_SECRET_ENV "OAUTH_CLIENT_SECRET"

typedef struct {
    char *client_secret;
} ServiceClass;

ServiceClass *create_service_class() {
    ServiceClass *service = (ServiceClass *)malloc(sizeof(ServiceClass));
    if (service == NULL) {
        return NULL;
    }

    service->client_secret = getenv(OAUTH_CLIENT_SECRET_ENV);
    if (service->client_secret == NULL) {
        fprintf(stderr, "OAuth client secret not found in environment variables.\n");
        free(service);
        return NULL;
    }

    return service;
}

void destroy_service_class(ServiceClass *service) {
    if (service != NULL) {
        free(service);
    }
}

int main() {
    ServiceClass *service = create_service_class();
    if (service == NULL) {
        fprintf(stderr, "Failed to create service class.\n");
        return 1;
    }

    printf("Service class created successfully.\n");
    printf("Client Secret: %s\n", service->client_secret);

    destroy_service_class(service);
    return 0;
}