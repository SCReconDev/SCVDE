#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define REGISTRY_PASSWORD_ENV_VAR "REGISTRY_PASSWORD"

typedef struct {
    char *deployment_name;
    char *registry_password;
} DeploymentHelper;

DeploymentHelper* create_deployment_helper(const char *deployment_name) {
    DeploymentHelper *helper = (DeploymentHelper*)malloc(sizeof(DeploymentHelper));
    if (helper == NULL) {
        return NULL;
    }

    helper->deployment_name = strdup(deployment_name);
    if (helper->deployment_name == NULL) {
        free(helper);
        return NULL;
    }

    const char *registry_password = getenv(REGISTRY_PASSWORD_ENV_VAR);
    if (registry_password == NULL) {
        fprintf(stderr, "Registry password not found in environment variables.\n");
        free(helper->deployment_name);
        free(helper);
        return NULL;
    }

    helper->registry_password = strdup(registry_password);
    if (helper->registry_password == NULL) {
        free(helper->deployment_name);
        free(helper);
        return NULL;
    }

    return helper;
}

void destroy_deployment_helper(DeploymentHelper *helper) {
    if (helper != NULL) {
        free(helper->deployment_name);
        free(helper->registry_password);
        free(helper);
    }
}

int main() {
    DeploymentHelper *helper = create_deployment_helper("Deployment1");
    if (helper == NULL) {
        fprintf(stderr, "Failed to create deployment helper.\n");
        return 1;
    }

    printf("Deployment helper created successfully.\n");
    printf("Deployment Name: %s\n", helper->deployment_name);
    printf("Registry Password: %s\n", helper->registry_password);

    destroy_deployment_helper(helper);
    return 0;
}