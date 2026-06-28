#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *service_name;
    char *client_secret;
} ServiceClass;

ServiceClass *create_service(const char *service_name) {
    ServiceClass *service = (ServiceClass *)malloc(sizeof(ServiceClass));
    if (service == NULL) {
        return NULL;
    }
    service->service_name = strdup(service_name);
    service->client_secret = getenv("CLIENT_SECRET");
    if (service->client_secret == NULL) {
        free(service->service_name);
        free(service);
        return NULL;
    }
    return service;
}

void destroy_service(ServiceClass *service) {
    if (service != NULL) {
        free(service->service_name);
        free(service->client_secret);
        free(service);
    }
}

int main() {
    ServiceClass *service = create_service("OAuthService");
    if (service == NULL) {
        fprintf(stderr, "Failed to create service\n");
        return 1;
    }
    printf("Service created with client secret: %s\n", service->client_secret);
    destroy_service(service);
    return 0;
}