#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CLIENT_SECRET_LENGTH 100

typedef struct {
    char client_secret[MAX_CLIENT_SECRET_LENGTH];
} ServiceClass;

ServiceClass* create_service_class() {
    ServiceClass* service = (ServiceClass*)malloc(sizeof(ServiceClass));
    if (service == NULL) {
        return NULL;
    }

    const char* client_secret_env = getenv("OAUTH_CLIENT_SECRET");
    if (client_secret_env == NULL) {
        fprintf(stderr, "OAUTH_CLIENT_SECRET environment variable not set\n");
        free(service);
        return NULL;
    }

    strncpy(service->client_secret, client_secret_env, MAX_CLIENT_SECRET_LENGTH - 1);
    service->client_secret[MAX_CLIENT_SECRET_LENGTH - 1] = '\0';

    return service;
}

void call_service(ServiceClass* service, const char* endpoint) {
    printf("Calling service endpoint %s with client secret: %s\n", endpoint, service->client_secret);
}

void destroy_service_class(ServiceClass* service) {
    if (service != NULL) {
        free(service);
    }
}

int main() {
    ServiceClass* service = create_service_class();
    if (service == NULL) {
        return 1;
    }

    call_service(service, "endpoint");
    destroy_service_class(service);

    return 0;
}