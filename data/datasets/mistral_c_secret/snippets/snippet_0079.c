#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OAUTH_CLIENT_SECRET "fake_oauth_client_secret_1234567890"

typedef struct {
    char *service_url;
    char *oauth_client_secret;
} ServiceClass;

ServiceClass *create_service_class(const char *service_url) {
    ServiceClass *service = (ServiceClass *)malloc(sizeof(ServiceClass));
    if (service == NULL) {
        return NULL;
    }

    service->service_url = strdup(service_url);
    service->oauth_client_secret = strdup(OAUTH_CLIENT_SECRET);

    return service;
}

void destroy_service_class(ServiceClass *service) {
    if (service != NULL) {
        free(service->service_url);
        free(service->oauth_client_secret);
        free(service);
    }
}

int call_service_api(ServiceClass *service, const char *endpoint) {
    if (service == NULL || endpoint == NULL) {
        return -1;
    }

    printf("Calling service API at %s%s with OAuth client secret %s\n", service->service_url, endpoint, service->oauth_client_secret);
    return 0;
}

int main() {
    ServiceClass *service = create_service_class("https://service.example.com");
    if (service == NULL) {
        fprintf(stderr, "Failed to create service class\n");
        return 1;
    }

    call_service_api(service, "/v1/data");

    destroy_service_class(service);
    return 0;
}