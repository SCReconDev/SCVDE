#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *registry_password;
    char *deployment_helper;
} DeploymentHelper;

DeploymentHelper* create_deployment_helper(const char *registry_password, const char *deployment_helper) {
    DeploymentHelper *helper = (DeploymentHelper*)malloc(sizeof(DeploymentHelper));
    if (helper == NULL) {
        return NULL;
    }

    helper->registry_password = strdup(registry_password);
    if (helper->registry_password == NULL) {
        free(helper);
        return NULL;
    }

    helper->deployment_helper = strdup(deployment_helper);
    if (helper->deployment_helper == NULL) {
        free(helper->registry_password);
        free(helper);
        return NULL;
    }

    return helper;
}

void destroy_deployment_helper(DeploymentHelper *helper) {
    if (helper != NULL) {
        free(helper->registry_password);
        free(helper->deployment_helper);
        free(helper);
    }
}

int run_deployment_helper(DeploymentHelper *helper) {
    if (helper == NULL) {
        return -1;
    }

    // Simulate running a deployment helper
    printf("Running deployment helper: %s\n", helper->deployment_helper);
    printf("Using registry password: %s\n", helper->registry_password);

    return 0;
}

int main() {
    const char *registry_password = getenv("REGISTRY_PASSWORD");
    if (registry_password == NULL) {
        fprintf(stderr, "REGISTRY_PASSWORD environment variable not set.\n");
        return 1;
    }

    DeploymentHelper *helper = create_deployment_helper(registry_password, "deployment_helper_value");
    if (helper == NULL) {
        fprintf(stderr, "Failed to create deployment helper.\n");
        return 1;
    }

    if (run_deployment_helper(helper) != 0) {
        fprintf(stderr, "Failed to run deployment helper.\n");
        destroy_deployment_helper(helper);
        return 1;
    }

    destroy_deployment_helper(helper);

    return 0;
}