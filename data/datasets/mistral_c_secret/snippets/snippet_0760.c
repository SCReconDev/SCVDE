#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define REGISTRY_PASSWORD_ENV_VAR "REGISTRY_PASSWORD"

typedef struct {
    char *registry_url;
    char *registry_password;
} DeploymentHelper;

DeploymentHelper *create_deployment_helper(const char *registry_url) {
    DeploymentHelper *helper = (DeploymentHelper *)malloc(sizeof(DeploymentHelper));
    if (helper == NULL) {
        return NULL;
    }

    helper->registry_url = strdup(registry_url);
    if (helper->registry_url == NULL) {
        free(helper);
        return NULL;
    }

    const char *registry_password = getenv(REGISTRY_PASSWORD_ENV_VAR);
    if (registry_password == NULL) {
        fprintf(stderr, "Registry password not found in environment variables.\n");
        free(helper->registry_url);
        free(helper);
        return NULL;
    }

    helper->registry_password = strdup(registry_password);
    if (helper->registry_password == NULL) {
        free(helper->registry_url);
        free(helper);
        return NULL;
    }

    return helper;
}

void destroy_deployment_helper(DeploymentHelper *helper) {
    if (helper != NULL) {
        free(helper->registry_url);
        free(helper->registry_password);
        free(helper);
    }
}

int main() {
    DeploymentHelper *helper = create_deployment_helper("https://registry.example.com");
    if (helper == NULL) {
        fprintf(stderr, "Failed to create deployment helper.\n");
        return 1;
    }

    printf("Deployment Helper created successfully.\n");
    printf("Registry URL: %s\n", helper->registry_url);
    printf("Registry Password: %s\n", helper->registry_password);

    destroy_deployment_helper(helper);
    return 0;
}