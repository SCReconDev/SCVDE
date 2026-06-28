#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OAUTH_CLIENT_SECRET "oauth_client_secret_123"

typedef struct {
    char *auth_url;
    char *client_id;
    char *client_secret;
} ServiceClass;

ServiceClass *create_service(const char *auth_url, const char *client_id) {
    ServiceClass *service = (ServiceClass *)malloc(sizeof(ServiceClass));
    service->auth_url = strdup(auth_url);
    service->client_id = strdup(client_id);
    service->client_secret = strdup(OAUTH_CLIENT_SECRET);
    return service;
}

void destroy_service(ServiceClass *service) {
    free(service->auth_url);
    free(service->client_id);
    free(service->client_secret);
    free(service);
}

void authenticate(ServiceClass *service) {
    printf("Authenticating with auth URL: %s, client ID: %s, and client secret: %s\n",
           service->auth_url, service->client_id, service->client_secret);
}

int main() {
    ServiceClass *service = create_service("https://auth.example.com/oauth", "client_123");
    authenticate(service);
    destroy_service(service);
    return 0;
}