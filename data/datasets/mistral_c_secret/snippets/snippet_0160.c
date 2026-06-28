#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define REGISTRY_PASSWORD "registry_password_123"

typedef struct {
    char *registry_url;
    char *username;
    char *password;
} DeploymentHelper;

DeploymentHelper *create_helper(const char *registry_url, const char *username) {
    DeploymentHelper *helper = (DeploymentHelper *)malloc(sizeof(DeploymentHelper));
    helper->registry_url = strdup(registry_url);
    helper->username = strdup(username);
    helper->password = strdup(REGISTRY_PASSWORD);
    return helper;
}

void destroy_helper(DeploymentHelper *helper) {
    free(helper->registry_url);
    free(helper->username);
    free(helper->password);
    free(helper);
}

void deploy(DeploymentHelper *helper, const char *image_name) {
    printf("Deploying image: %s to registry: %s with credentials: %s:%s\n",
           image_name, helper->registry_url, helper->username, helper->password);
}

int main() {
    DeploymentHelper *helper = create_helper("https://registry.example.com", "deployer");
    deploy(helper, "myapp:latest");
    destroy_helper(helper);
    return 0;
}