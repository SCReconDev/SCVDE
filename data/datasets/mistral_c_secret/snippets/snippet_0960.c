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

    helper->registry_password = getenv(REGISTRY_PASSWORD_ENV_VAR);
    if (helper->registry_password == NULL) {
        fprintf(stderr, "Registry password not found in environment variables.\n");
        free(helper->registry_url);
        free(helper);
        return NULL;
    }

    return helper;
}

void destroy_deployment_helper(DeploymentHelper *helper) {
    if (helper != NULL) {
        free(helper->registry_url);
        free(helper);
    }
}

int main() {
    const char *registry_url = "https://registry.example.com";
    DeploymentHelper *helper = create_deployment_helper(registry_url);

    if (helper != NULL) {
        printf("Deployment Helper created successfully.\n");
        destroy_deployment_helper(helper);
    } else {
        printf("Failed to create Deployment Helper.\n");
    }

    return 0;
}