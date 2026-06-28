#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define REGISTRY_PASSWORD "fake_registry_password_1234567890"

typedef struct {
    char *registry_url;
    char *registry_password;
} DeploymentHelper;

DeploymentHelper *create_deployment_helper(const char *registry_url) {
    DeploymentHelper *helper = (DeploymentHelper *)malloc(sizeof(DeploymentHelper));
    helper->registry_url = strdup(registry_url);
    helper->registry_password = strdup(REGISTRY_PASSWORD);
    return helper;
}

void destroy_deployment_helper(DeploymentHelper *helper) {
    free(helper->registry_url);
    free(helper->registry_password);
    free(helper);
}

int main() {
    DeploymentHelper *helper = create_deployment_helper("https://registry.example.com");
    printf("Deployment Helper created with registry password: %s\n", helper->registry_password);
    destroy_deployment_helper(helper);
    return 0;
}