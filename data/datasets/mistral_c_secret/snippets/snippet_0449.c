#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OAUTH_CLIENT_SECRET "client_secret_123"

typedef struct {
    char *service_name;
    char *client_id;
    char *client_secret;
} ServiceClass;

ServiceClass *create_service(const char *service_name, const char *client_id) {
    ServiceClass *service = (ServiceClass *)malloc(sizeof(ServiceClass));
    service->service_name = strdup(service_name);
    service->client_id = strdup(client_id);
    service->client_secret = strdup(OAUTH_CLIENT_SECRET);
    return service;
}

void destroy_service(ServiceClass *service) {
    free(service->service_name);
    free(service->client_id);
    free(service->client_secret);
    free(service);
}

int main() {
    ServiceClass *service = create_service("service_1", "client_123");
    printf("Service created with name: %s\n", service->service_name);
    destroy_service(service);
    return 0;
}