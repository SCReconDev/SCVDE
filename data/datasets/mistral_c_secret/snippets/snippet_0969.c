#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OAUTH_CLIENT_SECRET_ENV_VAR "OAUTH_CLIENT_SECRET"

typedef struct {
    char *service_name;
    char *client_id;
    char *client_secret;
} ServiceClass;

ServiceClass *create_service_class(const char *service_name, const char *client_id) {
    ServiceClass *service = (ServiceClass *)malloc(sizeof(ServiceClass));
    if (service == NULL) {
        return NULL;
    }

    service->service_name = strdup(service_name);
    if (service->service_name == NULL) {
        free(service);
        return NULL;
    }

    service->client_id = strdup(client_id);
    if (service->client_id == NULL) {
        free(service->service_name);
        free(service);
        return NULL;
    }

    char *client_secret = getenv(OAUTH_CLIENT_SECRET_ENV_VAR);
    if (client_secret == NULL) {
        fprintf(stderr, "OAuth client secret not found in environment variables.\n");
        free(service->client_id);
        free(service->service_name);
        free(service);
        return NULL;
    }

    service->client_secret = strdup(client_secret);
    if (service->client_secret == NULL) {
        free(service->client_id);
        free(service->service_name);
        free(service);
        return NULL;
    }

    return service;
}

void destroy_service_class(ServiceClass *service) {
    if (service != NULL) {
        free(service->service_name);
        free(service->client_id);
        free(service->client_secret);
        free(service);
    }
}

int main() {
    ServiceClass *service = create_service_class("my_service", "client_id_123");
    if (service == NULL) {
        fprintf(stderr, "Failed to create service class.\n");
        return 1;
    }

    printf("Service class created successfully.\n");
    printf("Service Name: %s\n", service->service_name);
    printf("Client ID: %s\n", service->client_id);

    destroy_service_class(service);
    return 0;
}