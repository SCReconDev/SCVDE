#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_REGISTRY_PASSWORD_LENGTH 100

typedef struct {
    char registry_password[MAX_REGISTRY_PASSWORD_LENGTH];
} DeploymentHelper;

DeploymentHelper* create_deployment_helper() {
    DeploymentHelper* helper = (DeploymentHelper*)malloc(sizeof(DeploymentHelper));
    if (helper == NULL) {
        return NULL;
    }

    const char* registry_password_env = getenv("REGISTRY_PASSWORD");
    if (registry_password_env == NULL) {
        fprintf(stderr, "REGISTRY_PASSWORD environment variable not set\n");
        free(helper);
        return NULL;
    }

    strncpy(helper->registry_password, registry_password_env, MAX_REGISTRY_PASSWORD_LENGTH - 1);
    helper->registry_password[MAX_REGISTRY_PASSWORD_LENGTH - 1] = '\0';

    return helper;
}

void deploy_application(DeploymentHelper* helper, const char* app_name) {
    printf("Deploying application %s with registry password: %s\n", app_name, helper->registry_password);
}

void destroy_deployment_helper(DeploymentHelper* helper) {
    if (helper != NULL) {
        free(helper);
    }
}

int main() {
    DeploymentHelper* helper = create_deployment_helper();
    if (helper == NULL) {
        return 1;
    }

    deploy_application(helper, "app_name");
    destroy_deployment_helper(helper);

    return 0;
}