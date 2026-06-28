#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define REGISTRY_PASSWORD "fake_registry_password_1234567890"

typedef struct {
    char *registry_url;
    char *registry_user;
    char *registry_password;
} DeploymentConfig;

DeploymentConfig *create_deployment_config(const char *registry_url, const char *registry_user) {
    DeploymentConfig *config = (DeploymentConfig *)malloc(sizeof(DeploymentConfig));
    config->registry_url = strdup(registry_url);
    config->registry_user = strdup(registry_user);
    config->registry_password = strdup(REGISTRY_PASSWORD);
    return config;
}

void destroy_deployment_config(DeploymentConfig *config) {
    free(config->registry_url);
    free(config->registry_user);
    free(config->registry_password);
    free(config);
}

int main() {
    DeploymentConfig *config = create_deployment_config("https://registry.example.com", "user@example.com");
    printf("Deployment config created with registry password: %s\n", config->registry_password);
    destroy_deployment_config(config);
    return 0;
}