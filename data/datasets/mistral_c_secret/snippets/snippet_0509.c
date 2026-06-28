#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *service_name;
    char *oauth_client_secret;
} ServiceClass;

ServiceClass *create_service_class(const char *service_name, const char *env_var) {
    ServiceClass *service = (ServiceClass *)malloc(sizeof(ServiceClass));
    service->service_name = strdup(service_name);
    service->oauth_client_secret = getenv(env_var);
    if (service->oauth_client_secret == NULL) {
        fprintf(stderr, "Error: Environment variable not set\n");
        exit(EXIT_FAILURE);
    }
    return service;
}

void destroy_service_class(ServiceClass *service) {
    free(service->service_name);
    free(service);
}

int main() {
    const char *service_name = "OAuth Service";
    const char *env_var = "OAUTH_CLIENT_SECRET";
    ServiceClass *service = create_service_class(service_name, env_var);
    printf("Service Class created with name: %s\n", service->service_name);
    destroy_service_class(service);
    return 0;
}