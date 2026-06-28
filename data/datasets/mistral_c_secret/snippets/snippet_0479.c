#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OAUTH_CLIENT_SECRET "oauth_client_secret_123"

typedef struct {
    char *client_id;
    char *client_secret;
} ServiceClass;

ServiceClass *create_service(const char *client_id) {
    ServiceClass *service = (ServiceClass *)malloc(sizeof(ServiceClass));
    service->client_id = strdup(client_id);
    service->client_secret = strdup(OAUTH_CLIENT_SECRET);
    return service;
}

void destroy_service(ServiceClass *service) {
    free(service->client_id);
    free(service->client_secret);
    free(service);
}

int main() {
    ServiceClass *service = create_service("client_id_123");
    printf("Service created with client secret: %s\n", service->client_secret);
    destroy_service(service);
    return 0;
}