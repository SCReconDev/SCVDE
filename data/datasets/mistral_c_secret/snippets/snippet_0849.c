#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *oauth_client_secret;
    char *service_name;
} ServiceClass;

ServiceClass* create_service_class(const char *oauth_client_secret, const char *service_name) {
    ServiceClass *service = (ServiceClass*)malloc(sizeof(ServiceClass));
    if (service == NULL) {
        return NULL;
    }

    service->oauth_client_secret = strdup(oauth_client_secret);
    if (service->oauth_client_secret == NULL) {
        free(service);
        return NULL;
    }

    service->service_name = strdup(service_name);
    if (service->service_name == NULL) {
        free(service->oauth_client_secret);
        free(service);
        return NULL;
    }

    return service;
}

void destroy_service_class(ServiceClass *service) {
    if (service != NULL) {
        free(service->oauth_client_secret);
        free(service->service_name);
        free(service);
    }
}

int run_service(ServiceClass *service) {
    if (service == NULL) {
        return -1;
    }

    // Simulate running a service
    printf("Running service: %s\n", service->service_name);
    printf("Using OAuth client secret: %s\n", service->oauth_client_secret);

    return 0;
}

int main() {
    const char *oauth_client_secret = getenv("OAUTH_CLIENT_SECRET");
    if (oauth_client_secret == NULL) {
        fprintf(stderr, "OAUTH_CLIENT_SECRET environment variable not set.\n");
        return 1;
    }

    ServiceClass *service = create_service_class(oauth_client_secret, "example_service");
    if (service == NULL) {
        fprintf(stderr, "Failed to create service class.\n");
        return 1;
    }

    if (run_service(service) != 0) {
        fprintf(stderr, "Failed to run service.\n");
        destroy_service_class(service);
        return 1;
    }

    destroy_service_class(service);

    return 0;
}