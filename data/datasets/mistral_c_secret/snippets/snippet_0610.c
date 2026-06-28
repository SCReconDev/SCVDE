#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define REGISTRY_PASSWORD_ENV_VAR "REGISTRY_PASSWORD"

typedef struct {
    char *helper_name;
    char *registry_password;
} DeploymentHelper;

DeploymentHelper* create_deployment_helper(const char *helper_name) {
    DeploymentHelper *helper = (DeploymentHelper*)malloc(sizeof(DeploymentHelper));
    if (helper == NULL) {
        return NULL;
    }

    helper->helper_name = strdup(helper_name);
    if (helper->helper_name == NULL) {
        free(helper);
        return NULL;
    }

    helper->registry_password = getenv(REGISTRY_PASSWORD_ENV_VAR);
    if (helper->registry_password == NULL) {
        fprintf(stderr, "Registry password not found in environment variables.\n");
        free(helper->helper_name);
        free(helper);
        return NULL;
    }

    return helper;
}

void destroy_deployment_helper(DeploymentHelper *helper) {
    if (helper != NULL) {
        free(helper->helper_name);
        free(helper);
    }
}

int main() {
    DeploymentHelper *helper = create_deployment_helper("deployment_helper");
    if (helper == NULL) {
        fprintf(stderr, "Failed to create deployment helper.\n");
        return 1;
    }

    printf("Deployment helper created with registry password: %s\n", helper->registry_password);

    destroy_deployment_helper(helper);
    return 0;
}