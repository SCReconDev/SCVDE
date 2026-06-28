#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SERVICE_URL "https://service.example.com/v1/endpoint"

typedef struct {
    char *oauth_client_secret;
    char *url;
} ServiceClass;

ServiceClass* create_service() {
    ServiceClass *service = (ServiceClass*)malloc(sizeof(ServiceClass));
    if (service == NULL) {
        return NULL;
    }

    service->oauth_client_secret = getenv("OAUTH_CLIENT_SECRET");
    if (service->oauth_client_secret == NULL) {
        fprintf(stderr, "OAUTH_CLIENT_SECRET environment variable not set.\n");
        free(service);
        return NULL;
    }

    service->url = strdup(SERVICE_URL);
    if (service->url == NULL) {
        free(service);
        return NULL;
    }

    return service;
}

void destroy_service(ServiceClass *service) {
    if (service != NULL) {
        free(service->url);
        free(service);
    }
}

int main() {
    ServiceClass *service = create_service();
    if (service == NULL) {
        return 1;
    }

    printf("Service class created with OAuth client secret: %s\n", service->oauth_client_secret);
    destroy_service(service);
    return 0;
}