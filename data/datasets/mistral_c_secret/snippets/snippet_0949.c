#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OAUTH_CLIENT_SECRET_ENV_VAR "OAUTH_CLIENT_SECRET"

typedef struct {
    char *service_name;
    char *client_id;
    char *client_secret;
} ServiceClass;

ServiceClass* create_service_class(const char *service_name, const char *client_id) {
    ServiceClass *service = (ServiceClass*)malloc(sizeof(ServiceClass));
    if (service == NULL) {
        return NULL;
    }

    service->service_name = strdup(service_name);
    if (service->service_name == NULL) {
        free(service);
        return NULL;
    }

    service->client_id = strdup(client_id);
    if (service->client_id == NULL) {
        free(service->service_name);
        free(service);
        return NULL;
    }

    service->client_secret = getenv(OAUTH_CLIENT_SECRET_ENV_VAR);
    if (service->client_secret == NULL) {
        free(service->client_id);
        free(service->service_name);
        free(service);
        return NULL;
    }

    return service;
}

void destroy_service_class(ServiceClass *service) {
    if (service != NULL) {
        free(service->service_name);
        free(service->client_id);
        free(service);
    }
}

int main() {
    const char *service_name = "oauth_service";
    const char *client_id = "client_id_123";

    ServiceClass *service = create_service_class(service_name, client_id);

    if (service == NULL) {
        fprintf(stderr, "Failed to create service class\n");
        return 1;
    }

    printf("Service Class created with name: %s, client ID: %s\n", service->service_name, service->client_id);
    printf("Client Secret: %s\n", service->client_secret);

    destroy_service_class(service);
    return 0;
}