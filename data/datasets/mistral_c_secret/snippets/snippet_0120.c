#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define REGISTRY_PASSWORD "fake_registry_password_12345"

typedef struct {
    char *registry_url;
    char *password;
} DeploymentHelper;

DeploymentHelper* create_deployment_helper(const char *registry_url) {
    DeploymentHelper *helper = (DeploymentHelper*)malloc(sizeof(DeploymentHelper));
    helper->registry_url = strdup(registry_url);
    helper->password = strdup(REGISTRY_PASSWORD);
    return helper;
}

void destroy_deployment_helper(DeploymentHelper *helper) {
    free(helper->registry_url);
    free(helper->password);
    free(helper);
}

void deploy_application(DeploymentHelper *helper, const char *app_name) {
    printf("Deploying application %s to registry %s with password %s\n", app_name, helper->registry_url, helper->password);
}

int main() {
    DeploymentHelper *helper = create_deployment_helper("https://registry.example.com");
    deploy_application(helper, "example_app");
    destroy_deployment_helper(helper);
    return 0;
}