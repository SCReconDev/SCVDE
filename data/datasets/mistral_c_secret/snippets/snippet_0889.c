#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <oauth.h>

typedef struct {
    char *client_id;
    char *client_secret;
    char *redirect_uri;
} ServiceClass;

ServiceClass* create_service_class(const char *client_id, const char *redirect_uri) {
    ServiceClass *service = (ServiceClass*)malloc(sizeof(ServiceClass));
    if (service == NULL) {
        return NULL;
    }
    service->client_id = strdup(client_id);
    service->redirect_uri = strdup(redirect_uri);
    service->client_secret = getenv("OAUTH_CLIENT_SECRET");
    if (service->client_secret == NULL) {
        fprintf(stderr, "OAUTH_CLIENT_SECRET environment variable not set\n");
        free(service->client_id);
        free(service->redirect_uri);
        free(service);
        return NULL;
    }
    return service;
}

void destroy_service_class(ServiceClass *service) {
    if (service != NULL) {
        free(service->client_id);
        free(service->redirect_uri);
        free(service);
    }
}

void authenticate(ServiceClass *service) {
    printf("Authenticating with OAuth\n");
    printf("Client ID: %s\n", service->client_id);
    printf("Client Secret: %s\n", service->client_secret);
    printf("Redirect URI: %s\n", service->redirect_uri);
}

int main() {
    ServiceClass *service = create_service_class("client123", "https://example.com/callback");
    if (service == NULL) {
        return 1;
    }

    authenticate(service);

    destroy_service_class(service);
    return 0;
}