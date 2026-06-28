#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define REGISTRY_PASSWORD "fake_registry_password_1234567890"

typedef struct {
    char *registry_url;
    char *registry_user;
    char *registry_password;
} DeploymentHelper;

DeploymentHelper* create_helper(const char *registry_url, const char *registry_user) {
    DeploymentHelper *helper = (DeploymentHelper*)malloc(sizeof(DeploymentHelper));
    helper->registry_url = strdup(registry_url);
    helper->registry_user = strdup(registry_user);
    helper->registry_password = strdup(REGISTRY_PASSWORD);
    return helper;
}

void destroy_helper(DeploymentHelper *helper) {
    free(helper->registry_url);
    free(helper->registry_user);
    free(helper->registry_password);
    free(helper);
}

void deploy_image(DeploymentHelper *helper, const char *image_name) {
    printf("Deploying image: %s\n", image_name);
    printf("Using registry URL: %s\n", helper->registry_url);
    printf("Using registry user: %s\n", helper->registry_user);
    printf("Using registry password: %s\n", helper->registry_password);
}

int main() {
    DeploymentHelper *helper = create_helper("https://registry.example.com/", "deploy_user");
    deploy_image(helper, "example_image:latest");
    destroy_helper(helper);
    return 0;
}