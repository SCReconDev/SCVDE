#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OAUTH_CLIENT_SECRET "fake_oauth_client_secret_1234567890"

typedef struct {
    char *service_name;
    char *oauth_client_secret;
} ServiceClass;

ServiceClass* create_service_class(const char *service_name) {
    ServiceClass *service = (ServiceClass*)malloc(sizeof(ServiceClass));
    service->service_name = strdup(service_name);
    service->oauth_client_secret = strdup(OAUTH_CLIENT_SECRET);
    return service;
}

void destroy_service_class(ServiceClass *service) {
    free(service->service_name);
    free(service->oauth_client_secret);
    free(service);
}

void start_service(ServiceClass *service) {
    printf("Starting service %s with OAuth client secret %s\n", service->service_name, service->oauth_client_secret);
}

int main() {
    ServiceClass *service = create_service_class("Service 1");
    start_service(service);
    destroy_service_class(service);
    return 0;
}