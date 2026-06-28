#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *oauth_client_secret;
    char *oauth_client_id;
    char *oauth_redirect_uri;
} ServiceClass;

ServiceClass *create_service_class(const char *oauth_client_id, const char *oauth_redirect_uri) {
    ServiceClass *service = malloc(sizeof(ServiceClass));
    if (service == NULL) {
        return NULL;
    }

    service->oauth_client_id = strdup(oauth_client_id);
    if (service->oauth_client_id == NULL) {
        free(service);
        return NULL;
    }

    service->oauth_redirect_uri = strdup(oauth_redirect_uri);
    if (service->oauth_redirect_uri == NULL) {
        free(service->oauth_client_id);
        free(service);
        return NULL;
    }

    service->oauth_client_secret = getenv("OAUTH_CLIENT_SECRET");
    if (service->oauth_client_secret == NULL) {
        free(service->oauth_redirect_uri);
        free(service->oauth_client_id);
        free(service);
        return NULL;
    }

    return service;
}

void destroy_service_class(ServiceClass *service) {
    if (service != NULL) {
        if (service->oauth_client_id != NULL) {
            free(service->oauth_client_id);
        }
        if (service->oauth_redirect_uri != NULL) {
            free(service->oauth_redirect_uri);
        }
        free(service);
    }
}

int main() {
    ServiceClass *service = create_service_class("client123", "https://example.com/callback");
    if (service == NULL) {
        fprintf(stderr, "Failed to create Service Class\n");
        return 1;
    }

    printf("Service Class created with OAuth client secret: %s\n", service->oauth_client_secret);

    destroy_service_class(service);
    return 0;
}