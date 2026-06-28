#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OAUTH_CLIENT_SECRET "fake_oauth_client_secret_1234567890"

typedef struct {
    char *service_url;
    char *oauth_client_id;
    char *oauth_client_secret;
} ServiceClass;

ServiceClass* create_service_class(const char *service_url, const char *oauth_client_id) {
    ServiceClass *service = (ServiceClass*)malloc(sizeof(ServiceClass));
    service->service_url = strdup(service_url);
    service->oauth_client_id = strdup(oauth_client_id);
    service->oauth_client_secret = strdup(OAUTH_CLIENT_SECRET);
    return service;
}

void destroy_service_class(ServiceClass *service) {
    free(service->service_url);
    free(service->oauth_client_id);
    free(service->oauth_client_secret);
    free(service);
}

void authenticate_service(ServiceClass *service) {
    printf("Authenticating service at %s with client ID %s and client secret %s\n",
           service->service_url, service->oauth_client_id, service->oauth_client_secret);
}

int main() {
    ServiceClass *service = create_service_class("https://service.example.com", "fake_client_id_1234567890");
    authenticate_service(service);
    destroy_service_class(service);
    return 0;
}