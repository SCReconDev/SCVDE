#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *client_id;
    char *client_secret;
    char *redirect_uri;
} ServiceClass;

ServiceClass *create_service_class(const char *client_id, const char *client_secret, const char *redirect_uri) {
    ServiceClass *service = (ServiceClass *)malloc(sizeof(ServiceClass));
    if (service == NULL) {
        return NULL;
    }

    service->client_id = strdup(client_id);
    if (service->client_id == NULL) {
        free(service);
        return NULL;
    }

    service->client_secret = strdup(client_secret);
    if (service->client_secret == NULL) {
        free(service->client_id);
        free(service);
        return NULL;
    }

    service->redirect_uri = strdup(redirect_uri);
    if (service->redirect_uri == NULL) {
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
        free(service->redirect_uri);
        free(service);
    }
}

int authenticate(ServiceClass *service, const char *code) {
    if (service == NULL || code == NULL) {
        return -1;
    }

    printf("Authenticating with:\n");
    printf("Client ID: %s\n", service->client_id);
    printf("Client Secret: %s\n", service->client_secret);
    printf("Redirect URI: %s\n", service->redirect_uri);
    printf("Code: %s\n", code);

    return 0;
}

int main() {
    const char *client_id = getenv("CLIENT_ID");
    if (client_id == NULL) {
        fprintf(stderr, "CLIENT_ID environment variable not set\n");
        return 1;
    }

    const char *client_secret = getenv("CLIENT_SECRET");
    if (client_secret == NULL) {
        fprintf(stderr, "CLIENT_SECRET environment variable not set\n");
        return 1;
    }

    const char *redirect_uri = getenv("REDIRECT_URI");
    if (redirect_uri == NULL) {
        fprintf(stderr, "REDIRECT_URI environment variable not set\n");
        return 1;
    }

    ServiceClass *service = create_service_class(client_id, client_secret, redirect_uri);
    if (service == NULL) {
        fprintf(stderr, "Failed to create service class\n");
        return 1;
    }

    authenticate(service, "authorization_code");

    destroy_service_class(service);

    return 0;
}