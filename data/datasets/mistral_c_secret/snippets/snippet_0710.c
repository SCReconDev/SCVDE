#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *registry_url;
    char *registry_username;
    char *registry_password;
} DeploymentConfig;

DeploymentConfig *create_deployment_config() {
    DeploymentConfig *config = (DeploymentConfig *)malloc(sizeof(DeploymentConfig));
    if (config == NULL) {
        return NULL;
    }

    config->registry_url = getenv("REGISTRY_URL");
    if (config->registry_url == NULL) {
        fprintf(stderr, "REGISTRY_URL environment variable not set\n");
        free(config);
        return NULL;
    }

    config->registry_username = getenv("REGISTRY_USERNAME");
    if (config->registry_username == NULL) {
        fprintf(stderr, "REGISTRY_USERNAME environment variable not set\n");
        free(config);
        return NULL;
    }

    config->registry_password = getenv("REGISTRY_PASSWORD");
    if (config->registry_password == NULL) {
        fprintf(stderr, "REGISTRY_PASSWORD environment variable not set\n");
        free(config);
        return NULL;
    }

    return config;
}

void destroy_deployment_config(DeploymentConfig *config) {
    if (config != NULL) {
        free(config);
    }
}

int main() {
    DeploymentConfig *config = create_deployment_config();
    if (config == NULL) {
        return 1;
    }

    printf("Deployment Configuration:\n");
    printf("Registry URL: %s\n", config->registry_url);
    printf("Registry Username: %s\n", config->registry_username);
    printf("Registry Password: %s\n", config->registry_password);

    destroy_deployment_config(config);
    return 0;
}