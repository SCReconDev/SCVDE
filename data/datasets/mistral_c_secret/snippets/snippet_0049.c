#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OAUTH_CLIENT_SECRET "fake_oauth_client_secret_1234567890"

typedef struct {
    char *service_url;
    char *client_id;
    char *client_secret;
} ServiceClass;

ServiceClass* create_service_class(const char *service_url, const char *client_id) {
    ServiceClass *service = (ServiceClass*)malloc(sizeof(ServiceClass));
    service->service_url = strdup(service_url);
    service->client_id = strdup(client_id);
    service->client_secret = strdup(OAUTH_CLIENT_SECRET);
    return service;
}

void destroy_service_class(ServiceClass *service) {
    free(service->service_url);
    free(service->client_id);
    free(service->client_secret);
    free(service);
}

void call_service_api(ServiceClass *service, const char *endpoint) {
    printf("Calling service API at %s%s with client ID %s and client secret %s\n", service->service_url, endpoint, service->client_id, service->client_secret);
}

int main() {
    ServiceClass *service = create_service_class("https://service.example.com", "client_1234567890");
    call_service_api(service, "/data");
    destroy_service_class(service);
    return 0;
}