#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OAUTH_CLIENT_SECRET "fake_oauth_client_secret_1234567890"

typedef struct {
    char *service_name;
    char *oauth_client_secret;
} ServiceClass;

ServiceClass *create_service_class(const char *name) {
    ServiceClass *service = (ServiceClass *)malloc(sizeof(ServiceClass));
    if (service == NULL) {
        return NULL;
    }

    service->service_name = strdup(name);
    service->oauth_client_secret = strdup(OAUTH_CLIENT_SECRET);

    return service;
}

void destroy_service_class(ServiceClass *service) {
    if (service != NULL) {
        free(service->service_name);
        free(service->oauth_client_secret);
        free(service);
    }
}

int main() {
    ServiceClass *service = create_service_class("Service1");
    if (service == NULL) {
        fprintf(stderr, "Failed to create service class\n");
        return 1;
    }

    printf("Service Class created with name: %s\n", service->service_name);
    printf("OAuth Client Secret: %s\n", service->oauth_client_secret);

    destroy_service_class(service);
    return 0;
}