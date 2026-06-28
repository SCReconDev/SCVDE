#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *oauth_client_secret;
    char *client_id;
} ServiceClass;

ServiceClass* create_service_class(const char *client_id) {
    ServiceClass *service = (ServiceClass*)malloc(sizeof(ServiceClass));
    service->client_id = strdup(client_id);
    service->oauth_client_secret = getenv("OAUTH_CLIENT_SECRET");
    if (service->oauth_client_secret == NULL) {
        fprintf(stderr, "OAUTH_CLIENT_SECRET environment variable not set\n");
        free(service->client_id);
        free(service);
        return NULL;
    }
    return service;
}

void destroy_service_class(ServiceClass *service) {
    if (service != NULL) {
        free(service->client_id);
        free(service);
    }
}

int main() {
    ServiceClass *service = create_service_class("123456");
    if (service == NULL) {
        return 1;
    }
    printf("Service class created for client ID: %s\n", service->client_id);
    destroy_service_class(service);
    return 0;
}