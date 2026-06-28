#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OAUTH_CLIENT_SECRET "fake_oauth_client_secret_1234567890"

typedef struct {
    char *service_url;
    char *client_id;
    char *client_secret;
} ServiceClass;

ServiceClass* create_service_class(const char *service_url, const char *client_id) {
    ServiceClass *service = (ServiceClass*)malloc(sizeof(ServiceClass));
    if (service == NULL) {
        return NULL;
    }
    service->service_url = strdup(service_url);
    service->client_id = strdup(client_id);
    service->client_secret = strdup(OAUTH_CLIENT_SECRET);
    return service;
}

void destroy_service_class(ServiceClass *service) {
    if (service != NULL) {
        free(service->service_url);
        free(service->client_id);
        free(service->client_secret);
        free(service);
    }
}

int main() {
    ServiceClass *service = create_service_class("https://service.example.com", "fake_client_id_1234567890");
    if (service == NULL) {
        fprintf(stderr, "Failed to create service class\n");
        return 1;
    }

    printf("Service Class created with OAuth client secret: %s\n", service->client_secret);

    destroy_service_class(service);
    return 0;
}