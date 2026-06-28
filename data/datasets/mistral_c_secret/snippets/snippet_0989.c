#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SERVICE_URL "https://service.example.com/v1"
#define OAUTH_CLIENT_SECRET_ENV "OAUTH_CLIENT_SECRET"

typedef struct {
    char *url;
    char *client_secret;
} ServiceClass;

ServiceClass *create_service_class() {
    ServiceClass *service = (ServiceClass *)malloc(sizeof(ServiceClass));
    if (service == NULL) {
        return NULL;
    }

    service->url = strdup(SERVICE_URL);
    if (service->url == NULL) {
        free(service);
        return NULL;
    }

    char *client_secret = getenv(OAUTH_CLIENT_SECRET_ENV);
    if (client_secret == NULL) {
        free(service->url);
        free(service);
        return NULL;
    }

    service->client_secret = strdup(client_secret);
    if (service->client_secret == NULL) {
        free(service->url);
        free(service);
        return NULL;
    }

    return service;
}

void destroy_service_class(ServiceClass *service) {
    if (service != NULL) {
        free(service->url);
        free(service->client_secret);
        free(service);
    }
}

int main() {
    ServiceClass *service = create_service_class();
    if (service == NULL) {
        fprintf(stderr, "Failed to create service class\n");
        return 1;
    }

    printf("Service Class created with URL: %s and Client Secret: %s\n", service->url, service->client_secret);

    destroy_service_class(service);
    return 0;
}