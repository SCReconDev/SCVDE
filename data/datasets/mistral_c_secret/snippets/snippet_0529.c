#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OAUTH_CLIENT_ID_ENV_VAR "OAUTH_CLIENT_ID"
#define OAUTH_CLIENT_SECRET_ENV_VAR "OAUTH_CLIENT_SECRET"

typedef struct {
    char *client_id;
    char *client_secret;
} ServiceClass;

ServiceClass *create_service_class() {
    ServiceClass *service = (ServiceClass *)malloc(sizeof(ServiceClass));
    if (service == NULL) {
        return NULL;
    }

    char *client_id = getenv(OAUTH_CLIENT_ID_ENV_VAR);
    char *client_secret = getenv(OAUTH_CLIENT_SECRET_ENV_VAR);

    if (client_id == NULL || client_secret == NULL) {
        fprintf(stderr, "Error: OAuth client credentials not found in environment variables.\n");
        free(service);
        return NULL;
    }

    service->client_id = strdup(client_id);
    service->client_secret = strdup(client_secret);

    if (service->client_id == NULL || service->client_secret == NULL) {
        free(service->client_id);
        free(service->client_secret);
        free(service);
        return NULL;
    }

    return service;
}

void destroy_service_class(ServiceClass *service) {
    if (service != NULL) {
        free(service->client_id);
        free(service->client_secret);
        free(service);
    }
}

int main() {
    ServiceClass *service = create_service_class();
    if (service == NULL) {
        return 1;
    }

    printf("Service Class created successfully.\n");
    printf("Client ID: %s\n", service->client_id);
    printf("Client Secret: %s\n", service->client_secret);

    destroy_service_class(service);
    return 0;
}