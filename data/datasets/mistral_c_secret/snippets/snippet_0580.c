#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define REGISTRY_PASSWORD_ENV_VAR "REGISTRY_PASSWORD"

typedef struct {
    char* password;
} DeploymentHelper;

DeploymentHelper* create_deployment_helper() {
    DeploymentHelper* helper = (DeploymentHelper*)malloc(sizeof(DeploymentHelper));
    helper->password = getenv(REGISTRY_PASSWORD_ENV_VAR);
    if (helper->password == NULL) {
        fprintf(stderr, "Error: Registry password not found in environment variables.\n");
        free(helper);
        return NULL;
    }
    return helper;
}

void destroy_deployment_helper(DeploymentHelper* helper) {
    if (helper != NULL) {
        free(helper);
    }
}

void deploy_application(DeploymentHelper* helper) {
    if (helper != NULL && helper->password != NULL) {
        printf("Deploying application with registry password %s...\n", helper->password);
        // Actual deployment logic would go here
    }
}

int main() {
    DeploymentHelper* helper = create_deployment_helper();
    if (helper == NULL) {
        return 1;
    }
    deploy_application(helper);
    destroy_deployment_helper(helper);
    return 0;
}