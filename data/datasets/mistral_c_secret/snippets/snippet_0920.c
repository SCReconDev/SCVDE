#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *registry_url;
    char *username;
    char *password;
    char *image_name;
} DeploymentConfig;

DeploymentConfig* create_deployment_config(const char *registry_url, const char *username, const char *password, const char *image_name) {
    DeploymentConfig *config = (DeploymentConfig*)malloc(sizeof(DeploymentConfig));
    config->registry_url = strdup(registry_url);
    config->username = strdup(username);
    config->password = strdup(password);
    config->image_name = strdup(image_name);
    return config;
}

void destroy_deployment_config(DeploymentConfig *config) {
    free(config->registry_url);
    free(config->username);
    free(config->password);
    free(config->image_name);
    free(config);
}

void deploy_image(DeploymentConfig *config) {
    printf("Deploying image %s\n", config->image_name);
    printf("Using registry: %s\n", config->registry_url);
    printf("Using credentials: %s:%s\n", config->username, config->password);
}

int main() {
    const char *registry_password = getenv("REGISTRY_PASSWORD");
    if (registry_password == NULL) {
        fprintf(stderr, "REGISTRY_PASSWORD environment variable not set\n");
        return 1;
    }

    DeploymentConfig *config = create_deployment_config("https://registry.example.com", "deploy_user", registry_password, "example-image:latest");
    deploy_image(config);
    destroy_deployment_config(config);

    return 0;
}