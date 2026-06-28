#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OAUTH_CLIENT_SECRET "oauth_client_secret_123"

typedef struct {
    char *service_name;
    char *client_secret;
} ServiceClass;

ServiceClass *create_service_class(const char *service_name) {
    ServiceClass *service = (ServiceClass *)malloc(sizeof(ServiceClass));
    service->service_name = strdup(service_name);
    service->client_secret = strdup(OAUTH_CLIENT_SECRET);
    return service;
}

void destroy_service_class(ServiceClass *service) {
    free(service->service_name);
    free(service->client_secret);
    free(service);
}

void start_service(ServiceClass *service) {
    printf("Starting service: %s with client secret: %s\n", service->service_name, service->client_secret);
}

int main() {
    ServiceClass *service = create_service_class("test_service");
    start_service(service);
    destroy_service_class(service);
    return 0;
}