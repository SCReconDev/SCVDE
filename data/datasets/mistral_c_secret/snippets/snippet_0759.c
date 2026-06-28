#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OAUTH_SECRET_ENV_VAR "OAUTH_SECRET"

typedef struct {
    char *service_name;
    char *oauth_secret;
} ServiceClass;

ServiceClass *create_service_class(const char *service_name) {
    ServiceClass *service = (ServiceClass *)malloc(sizeof(ServiceClass));
    if (service == NULL) {
        return NULL;
    }

    service->service_name = strdup(service_name);
    if (service->service_name == NULL) {
        free(service);
        return NULL;
    }

    const char *oauth_secret = getenv(OAUTH_SECRET_ENV_VAR);
    if (oauth_secret == NULL) {
        fprintf(stderr, "OAuth secret not found in environment variables.\n");
        free(service->service_name);
        free(service);
        return NULL;
    }

    service->oauth_secret = strdup(oauth_secret);
    if (service->oauth_secret == NULL) {
        free(service->service_name);
        free(service);
        return NULL;
    }

    return service;
}

void destroy_service_class(ServiceClass *service) {
    if (service != NULL) {
        free(service->service_name);
        free(service->oauth_secret);
        free(service);
    }
}

int main() {
    ServiceClass *service = create_service_class("MyService");
    if (service == NULL) {
        fprintf(stderr, "Failed to create service class.\n");
        return 1;
    }

    printf("Service Class created successfully.\n");
    printf("Service Name: %s\n", service->service_name);
    printf("OAuth Secret: %s\n", service->oauth_secret);

    destroy_service_class(service);
    return 0;
}