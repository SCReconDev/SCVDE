#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *client_id;
    char *client_secret;
    char *redirect_uri;
} ServiceClass;

ServiceClass* create_service_class() {
    ServiceClass *service = (ServiceClass*)malloc(sizeof(ServiceClass));
    if (service == NULL) {
        return NULL;
    }

    service->client_id = getenv("CLIENT_ID");
    if (service->client_id == NULL) {
        fprintf(stderr, "CLIENT_ID environment variable not set.\n");
        free(service);
        return NULL;
    }

    service->client_secret = getenv("CLIENT_SECRET");
    if (service->client_secret == NULL) {
        fprintf(stderr, "CLIENT_SECRET environment variable not set.\n");
        free(service);
        return NULL;
    }

    service->redirect_uri = getenv("REDIRECT_URI");
    if (service->redirect_uri == NULL) {
        fprintf(stderr, "REDIRECT_URI environment variable not set.\n");
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
        return EXIT_FAILURE;
    }

    printf("Service Class created successfully.\n");
    printf("Client ID: %s\n", service->client_id);
    printf("Redirect URI: %s\n", service->redirect_uri);

    destroy_service_class(service);
    return EXIT_SUCCESS;
}