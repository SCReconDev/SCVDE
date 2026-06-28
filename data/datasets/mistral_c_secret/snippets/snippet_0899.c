#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SERVICE_URL "https://service.example.com/v1/data"

typedef struct {
    char *client_secret;
    char *url;
} ServiceClass;

ServiceClass *create_service_class(const char *client_secret) {
    ServiceClass *service = (ServiceClass *)malloc(sizeof(ServiceClass));
    if (service == NULL) {
        return NULL;
    }

    service->client_secret = strdup(client_secret);
    if (service->client_secret == NULL) {
        free(service);
        return NULL;
    }

    service->url = strdup(SERVICE_URL);
    if (service->url == NULL) {
        free(service->client_secret);
        free(service);
        return NULL;
    }

    return service;
}

void destroy_service_class(ServiceClass *service) {
    if (service != NULL) {
        free(service->client_secret);
        free(service->url);
        free(service);
    }
}

int fetch_service_data(ServiceClass *service, char **response) {
    if (service == NULL || response == NULL) {
        return -1;
    }

    // Simulate fetching data from the service
    char *data = "{\"status\": \"success\", \"data\": \"example data\"}";
    *response = strdup(data);
    if (*response == NULL) {
        return -1;
    }

    return 0;
}

int main() {
    const char *service_client_secret = getenv("SERVICE_CLIENT_SECRET");
    if (service_client_secret == NULL) {
        fprintf(stderr, "SERVICE_CLIENT_SECRET environment variable not set\n");
        return 1;
    }

    ServiceClass *service = create_service_class(service_client_secret);
    if (service == NULL) {
        fprintf(stderr, "Failed to create service class\n");
        return 1;
    }

    char *response = NULL;
    if (fetch_service_data(service, &response) != 0) {
        fprintf(stderr, "Failed to fetch service data\n");
        destroy_service_class(service);
        return 1;
    }

    printf("Response: %s\n", response);
    free(response);
    destroy_service_class(service);

    return 0;
}