#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OAUTH_CLIENT_SECRET_ENV_VAR "OAUTH_CLIENT_SECRET"

typedef struct {
    char *oauth_url;
    char *client_secret;
} ServiceClass;

ServiceClass *create_service_class(const char *oauth_url) {
    ServiceClass *service = (ServiceClass *)malloc(sizeof(ServiceClass));
    if (service == NULL) {
        return NULL;
    }

    service->oauth_url = strdup(oauth_url);
    if (service->oauth_url == NULL) {
        free(service);
        return NULL;
    }

    service->client_secret = getenv(OAUTH_CLIENT_SECRET_ENV_VAR);
    if (service->client_secret == NULL) {
        fprintf(stderr, "OAuth client secret not found in environment variables\n");
        free(service->oauth_url);
        free(service);
        return NULL;
    }

    return service;
}

void destroy_service_class(ServiceClass *service) {
    if (service != NULL) {
        if (service->oauth_url != NULL) {
            free(service->oauth_url);
        }
        free(service);
    }
}

int main() {
    const char *oauth_url = "https://oauth.example.com";

    ServiceClass *service = create_service_class(oauth_url);

    if (service != NULL) {
        printf("Service class created successfully\n");
        destroy_service_class(service);
    } else {
        fprintf(stderr, "Failed to create service class\n");
    }

    return 0;
}