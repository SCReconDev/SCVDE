#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OAUTH_CLIENT_SECRET_ENV_VAR "OAUTH_CLIENT_SECRET"

typedef struct {
    char *service_name;
    char *oauth_client_secret;
} ServiceClass;

ServiceClass* create_service_class(const char *service_name) {
    ServiceClass *service = (ServiceClass*)malloc(sizeof(ServiceClass));
    if (service == NULL) {
        return NULL;
    }

    service->service_name = strdup(service_name);
    if (service->service_name == NULL) {
        free(service);
        return NULL;
    }

    service->oauth_client_secret = getenv(OAUTH_CLIENT_SECRET_ENV_VAR);
    if (service->oauth_client_secret == NULL) {
        fprintf(stderr, "OAuth client secret not found in environment variables.\n");
        free(service->service_name);
        free(service);
        return NULL;
    }

    return service;
}

void destroy_service_class(ServiceClass *service) {
    if (service != NULL) {
        free(service->service_name);
        free(service);
    }
}

int main() {
    ServiceClass *service = create_service_class("example_service");
    if (service == NULL) {
        fprintf(stderr, "Failed to create service class.\n");
        return 1;
    }

    printf("Service class created with OAuth client secret: %s\n", service->oauth_client_secret);

    destroy_service_class(service);
    return 0;
}