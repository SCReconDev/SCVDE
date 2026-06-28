#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OAUTH_CLIENT_SECRET_ENV_VAR "OAUTH_CLIENT_SECRET"

typedef struct {
    char *client_secret;
} ServiceClass;

ServiceClass* create_service() {
    ServiceClass *service = (ServiceClass*)malloc(sizeof(ServiceClass));
    service->client_secret = getenv(OAUTH_CLIENT_SECRET_ENV_VAR);
    if (service->client_secret == NULL) {
        fprintf(stderr, "Error: OAuth client secret not found in environment variables.\n");
        free(service);
        return NULL;
    }
    return service;
}

void destroy_service(ServiceClass *service) {
    if (service != NULL) {
        free(service);
    }
}

int authenticate(ServiceClass *service, const char *token) {
    if (service == NULL || service->client_secret == NULL || token == NULL) {
        return -1;
    }
    printf("Authenticating with token %s and client secret: %s\n", token, service->client_secret);
    return 0;
}

int main() {
    ServiceClass *service = create_service();
    if (service == NULL) {
        return EXIT_FAILURE;
    }
    authenticate(service, "test_token");
    destroy_service(service);
    return EXIT_SUCCESS;
}