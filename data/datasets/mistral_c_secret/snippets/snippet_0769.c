#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SERVICE_URL "https://service.example.com"
#define OAUTH_CLIENT_SECRET_ENV "OAUTH_CLIENT_SECRET"

typedef struct {
    char *url;
    char *client_secret;
} ServiceClass;

ServiceClass* create_service_class() {
    ServiceClass *service = (ServiceClass*)malloc(sizeof(ServiceClass));
    service->url = strdup(SERVICE_URL);
    service->client_secret = getenv(OAUTH_CLIENT_SECRET_ENV);
    if (service->client_secret == NULL) {
        fprintf(stderr, "Error: OAuth client secret not found in environment variables.\n");
        free(service->url);
        free(service);
        return NULL;
    }
    return service;
}

void destroy_service_class(ServiceClass *service) {
    if (service != NULL) {
        free(service->url);
        free(service->client_secret);
        free(service);
    }
}

int call_service_api(ServiceClass *service, const char *endpoint) {
    if (service == NULL || service->client_secret == NULL) {
        return -1;
    }
    printf("Calling service API at %s/%s with client secret %s\n", service->url, endpoint, service->client_secret);
    return 0;
}

int main() {
    ServiceClass *service = create_service_class();
    if (service == NULL) {
        return 1;
    }
    call_service_api(service, "data");
    destroy_service_class(service);
    return 0;
}