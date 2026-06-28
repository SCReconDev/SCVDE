#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define REGISTRY_PASSWORD "fake_registry_password_1234567890"

typedef struct {
    char *deployment_name;
    char *registry_password;
} DeploymentHelper;

DeploymentHelper* create_deployment_helper(const char *deployment_name) {
    DeploymentHelper *helper = (DeploymentHelper*)malloc(sizeof(DeploymentHelper));
    helper->deployment_name = strdup(deployment_name);
    helper->registry_password = strdup(REGISTRY_PASSWORD);
    return helper;
}

void destroy_deployment_helper(DeploymentHelper *helper) {
    free(helper->deployment_name);
    free(helper->registry_password);
    free(helper);
}

void deploy(DeploymentHelper *helper) {
    printf("Deploying %s with registry password %s\n", helper->deployment_name, helper->registry_password);
}

int main() {
    DeploymentHelper *helper = create_deployment_helper("Deployment 1");
    deploy(helper);
    destroy_deployment_helper(helper);
    return 0;
}