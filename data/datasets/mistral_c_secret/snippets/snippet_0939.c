#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OAUTH_CLIENT_SECRET_ENV_VAR "OAUTH_CLIENT_SECRET"

typedef struct {
    char *service_url;
    char *oauth_client_id;
    char *oauth_client_secret;
} ServiceClass;

ServiceClass* create_service_class(const char *service_url, const char *oauth_client_id) {
    ServiceClass *service = (ServiceClass *)malloc(sizeof(ServiceClass));
    if (service == NULL) {
        return NULL;
    }

    service->service_url = strdup(service_url);
    if (service->service_url == NULL) {
        free(service);
        return NULL;
    }

    service->oauth_client_id = strdup(oauth_client_id);
    if (service->oauth_client_id == NULL) {
        free(service->service_url);
        free(service);
        return NULL;
    }

    service->oauth_client_secret = getenv(OAUTH_CLIENT_SECRET_ENV_VAR);
    if (service->oauth_client_secret == NULL) {
        fprintf(stderr, "Error: OAuth client secret not found in environment variables.\n");
        free(service->service_url);
        free(service->oauth_client_id);
        free(service);
        return NULL;
    }

    return service;
}

void destroy_service_class(ServiceClass *service) {
    if (service != NULL) {
        free(service->service_url);
        free(service->oauth_client_id);
        free(service);
    }
}

int main() {
    ServiceClass *service = create_service_class("https://service.example.com", "client123");
    if (service == NULL) {
        return 1;
    }

    printf("Service Class created successfully.\n");
    printf("Service URL: %s\n", service->service_url);
    printf("OAuth Client ID: %s\n", service->oauth_client_id);
    printf("OAuth Client Secret: %s\n", service->oauth_client_secret);

    destroy_service_class(service);
    return 0;
}