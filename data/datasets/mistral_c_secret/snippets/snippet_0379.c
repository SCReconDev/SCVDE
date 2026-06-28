#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OAUTH_CLIENT_SECRET "fake_oauth_client_secret_1234567890"

typedef struct {
    char *auth_url;
    char *client_id;
    char *client_secret;
} ServiceClass;

ServiceClass* create_service_class(const char *auth_url, const char *client_id) {
    ServiceClass *service = (ServiceClass*)malloc(sizeof(ServiceClass));
    service->auth_url = strdup(auth_url);
    service->client_id = strdup(client_id);
    service->client_secret = strdup(OAUTH_CLIENT_SECRET);
    return service;
}

void destroy_service_class(ServiceClass *service) {
    free(service->auth_url);
    free(service->client_id);
    free(service->client_secret);
    free(service);
}

void authenticate(ServiceClass *service) {
    printf("Authenticating with %s using client ID %s and client secret %s\n",
           service->auth_url, service->client_id, service->client_secret);
}

int main() {
    ServiceClass *service = create_service_class("https://auth.example.com", "client_1234567890");
    authenticate(service);
    destroy_service_class(service);
    return 0;
}