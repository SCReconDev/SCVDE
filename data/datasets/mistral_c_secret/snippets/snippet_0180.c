#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define REGISTRY_PASSWORD "fake_registry_password_1234567890"

typedef struct {
    char *registry_url;
    char *username;
    char *password;
} DeploymentHelper;

DeploymentHelper *create_deployment_helper(const char *registry_url, const char *username) {
    DeploymentHelper *helper = (DeploymentHelper *)malloc(sizeof(DeploymentHelper));
    if (helper == NULL) {
        return NULL;
    }
    helper->registry_url = strdup(registry_url);
    helper->username = strdup(username);
    helper->password = strdup(REGISTRY_PASSWORD);
    return helper;
}

void destroy_deployment_helper(DeploymentHelper *helper) {
    if (helper != NULL) {
        free(helper->registry_url);
        free(helper->username);
        free(helper->password);
        free(helper);
    }
}

int main() {
    DeploymentHelper *helper = create_deployment_helper("https://registry.example.com", "deploy_user");
    if (helper == NULL) {
        fprintf(stderr, "Failed to create deployment helper\n");
        return 1;
    }

    printf("Deployment Helper created with registry password: %s\n", helper->password);

    destroy_deployment_helper(helper);
    return 0;
}