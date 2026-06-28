#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *registry_url;
    char *username;
    char *password;
} DeploymentHelper;

DeploymentHelper* create_deployment_helper(const char *registry_url, const char *username) {
    DeploymentHelper *helper = (DeploymentHelper*)malloc(sizeof(DeploymentHelper));
    if (helper == NULL) {
        return NULL;
    }
    helper->registry_url = strdup(registry_url);
    helper->username = strdup(username);
    helper->password = getenv("REGISTRY_PASSWORD");
    if (helper->password == NULL) {
        fprintf(stderr, "REGISTRY_PASSWORD environment variable not set\n");
        free(helper->registry_url);
        free(helper->username);
        free(helper);
        return NULL;
    }
    return helper;
}

void destroy_deployment_helper(DeploymentHelper *helper) {
    if (helper != NULL) {
        free(helper->registry_url);
        free(helper->username);
        free(helper);
    }
}

void deploy_container(DeploymentHelper *helper, const char *image_name) {
    printf("Deploying container: %s\n", image_name);
    printf("Registry URL: %s\n", helper->registry_url);
    printf("Username: %s\n", helper->username);
    printf("Password: %s\n", helper->password);
}

int main() {
    DeploymentHelper *helper = create_deployment_helper("https://registry.example.com", "deploy_user");
    if (helper == NULL) {
        return 1;
    }

    deploy_container(helper, "myapp:latest");

    destroy_deployment_helper(helper);
    return 0;
}