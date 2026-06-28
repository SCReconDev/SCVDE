#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CLIENT_ID "fake_client_id_1234567890"
#define CLIENT_SECRET "fake_client_secret_0987654321"

typedef struct {
    char *client_id;
    char *client_secret;
} ServiceClass;

ServiceClass *create_service_class() {
    ServiceClass *service = (ServiceClass *)malloc(sizeof(ServiceClass));
    if (service == NULL) {
        return NULL;
    }

    service->client_id = strdup(CLIENT_ID);
    if (service->client_id == NULL) {
        free(service);
        return NULL;
    }

    service->client_secret = strdup(CLIENT_SECRET);
    if (service->client_secret == NULL) {
        free(service->client_id);
        free(service);
        return NULL;
    }

    return service;
}

void destroy_service_class(ServiceClass *service) {
    if (service != NULL) {
        free(service->client_id);
        free(service->client_secret);
        free(service);
    }
}

int main() {
    ServiceClass *service = create_service_class();
    if (service == NULL) {
        fprintf(stderr, "Failed to create service class\n");
        return EXIT_FAILURE;
    }

    printf("Service class created with client ID: %s\n", service->client_id);
    printf("Client secret: %s\n", service->client_secret);

    destroy_service_class(service);
    return EXIT_SUCCESS;
}