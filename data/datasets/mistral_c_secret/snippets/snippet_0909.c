#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BUFFER_SIZE 1024

typedef struct {
    char *client_id;
    char *client_secret;
} ServiceClass;

ServiceClass* create_service_class(const char *client_id, const char *client_secret) {
    ServiceClass *service = (ServiceClass *)malloc(sizeof(ServiceClass));
    if (service == NULL) {
        return NULL;
    }

    service->client_id = strdup(client_id);
    service->client_secret = strdup(client_secret);

    if (service->client_id == NULL || service->client_secret == NULL) {
        free(service->client_id);
        free(service->client_secret);
        free(service);
        return NULL;
    }

    return service;
}

void destroy_service_class(ServiceClass *service) {
    if (service != NULL) {
        free(service->client_id);
        free(service->client_secret);
        free(service);
    }
}

int authenticate_service(ServiceClass *service, char *response_buffer, size_t buffer_size) {
    if (service == NULL || response_buffer == NULL || buffer_size < 1) {
        return -1;
    }

    char command[MAX_BUFFER_SIZE];
    snprintf(command, sizeof(command), "curl -X POST https://api.oauth.com/token -H \"Content-Type: application/x-www-form-urlencoded\" -d \"grant_type=client_credentials&client_id=%s&client_secret=%s\"", service->client_id, service->client_secret);

    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        return -1;
    }

    size_t bytes_read = fread(response_buffer, 1, buffer_size - 1, fp);
    response_buffer[bytes_read] = '\0';

    pclose(fp);

    return 0;
}

int main() {
    const char *client_id_env = getenv("OAUTH_CLIENT_ID");
    const char *client_secret_env = getenv("OAUTH_CLIENT_SECRET");

    if (client_id_env == NULL || client_secret_env == NULL) {
        fprintf(stderr, "OAUTH_CLIENT_ID or OAUTH_CLIENT_SECRET environment variable not set.\n");
        return 1;
    }

    ServiceClass *service = create_service_class(client_id_env, client_secret_env);
    if (service == NULL) {
        fprintf(stderr, "Failed to create service class.\n");
        return 1;
    }

    char response_buffer[MAX_BUFFER_SIZE];
    if (authenticate_service(service, response_buffer, sizeof(response_buffer)) != 0) {
        fprintf(stderr, "Failed to authenticate service.\n");
        destroy_service_class(service);
        return 1;
    }

    printf("Authentication Response: %s\n", response_buffer);

    destroy_service_class(service);

    return 0;
}