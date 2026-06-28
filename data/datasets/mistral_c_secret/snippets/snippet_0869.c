#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SERVICE_URL "https://service.example.com"
#define OAUTH_CLIENT_SECRET_ENV_VAR "OAUTH_CLIENT_SECRET"

typedef struct {
    char *url;
    char *client_secret;
} ServiceClass;

ServiceClass* create_service_class(const char *url) {
    ServiceClass *service = (ServiceClass*)malloc(sizeof(ServiceClass));
    if (service == NULL) {
        return NULL;
    }

    service->url = strdup(url);
    if (service->url == NULL) {
        free(service);
        return NULL;
    }

    service->client_secret = getenv(OAUTH_CLIENT_SECRET_ENV_VAR);
    if (service->client_secret == NULL) {
        fprintf(stderr, "OAuth client secret not found in environment variables.\n");
        free(service->url);
        free(service);
        return NULL;
    }

    return service;
}

void destroy_service_class(ServiceClass *service) {
    if (service != NULL) {
        if (service->url != NULL) {
            free(service->url);
        }
        free(service);
    }
}

int main() {
    ServiceClass *service = create_service_class(SERVICE_URL);
    if (service == NULL) {
        fprintf(stderr, "Failed to create service class.\n");
        return 1;
    }

    printf("Service Class created successfully.\n");
    printf("URL: %s\n", service->url);
    printf("Client Secret: %s\n", service->client_secret);

    destroy_service_class(service);
    return 0;
}