#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OAUTH_CLIENT_SECRET "client_secret_123"

typedef struct {
    char *client_id;
    char *client_secret;
} ServiceClass;

ServiceClass* create_service_class(const char *client_id) {
    ServiceClass *service = (ServiceClass*)malloc(sizeof(ServiceClass));
    service->client_id = strdup(client_id);
    service->client_secret = strdup(OAUTH_CLIENT_SECRET);
    return service;
}

void authenticate_service(ServiceClass *service) {
    printf("Authenticating service with client ID: %s and client secret: %s\n", service->client_id, service->client_secret);
}

void destroy_service_class(ServiceClass *service) {
    free(service->client_id);
    free(service->client_secret);
    free(service);
}

int main() {
    ServiceClass *service = create_service_class("client_id_123");
    authenticate_service(service);
    destroy_service_class(service);
    return 0;
}