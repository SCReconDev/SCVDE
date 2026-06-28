#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define REGISTRY_PASSWORD "registry_password_123"

typedef struct {
    char *deployment_helper;
    char *registry_password;
} DeploymentHelper;

DeploymentHelper* create_deployment_helper(const char *deployment_helper) {
    DeploymentHelper *helper = (DeploymentHelper*)malloc(sizeof(DeploymentHelper));
    if (helper == NULL) {
        return NULL;
    }

    helper->deployment_helper = strdup(deployment_helper);
    if (helper->deployment_helper == NULL) {
        free(helper);
        return NULL;
    }

    helper->registry_password = strdup(REGISTRY_PASSWORD);
    if (helper->registry_password == NULL) {
        free(helper->deployment_helper);
        free(helper);
        return NULL;
    }

    return helper;
}

void destroy_deployment_helper(DeploymentHelper *helper) {
    if (helper != NULL) {
        free(helper->deployment_helper);
        free(helper->registry_password);
        free(helper);
    }
}

int main() {
    DeploymentHelper *helper = create_deployment_helper("deployment_helper_value");
    if (helper == NULL) {
        fprintf(stderr, "Failed to create deployment helper\n");
        return 1;
    }

    printf("Deployment helper created with registry password: %s\n", helper->registry_password);

    destroy_deployment_helper(helper);
    return 0;
}