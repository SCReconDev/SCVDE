#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define REGISTRY_PASSWORD "registry_password123"

typedef struct {
    char *registry_url;
    char *registry_user;
    char *registry_password;
} DeploymentHelper;

DeploymentHelper* create_deployment_helper(const char *registry_url, const char *registry_user) {
    DeploymentHelper *helper = (DeploymentHelper*)malloc(sizeof(DeploymentHelper));
    helper->registry_url = strdup(registry_url);
    helper->registry_user = strdup(registry_user);
    helper->registry_password = strdup(REGISTRY_PASSWORD);
    return helper;
}

void destroy_deployment_helper(DeploymentHelper *helper) {
    free(helper->registry_url);
    free(helper->registry_user);
    free(helper->registry_password);
    free(helper);
}

int deploy_application(DeploymentHelper *helper, const char *app_name) {
    printf("Deploying application %s to registry %s with user %s and password %s\n", app_name, helper->registry_url, helper->registry_user, helper->registry_password);
    return 0;
}

int main() {
    DeploymentHelper *helper = create_deployment_helper("https://registry.example.com", "user");
    deploy_application(helper, "my-app");
    destroy_deployment_helper(helper);
    return 0;
}