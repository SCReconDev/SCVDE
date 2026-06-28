#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define REGISTRY_URL "https://registry.example.com"

typedef struct {
    char *registry_password;
    char *registry_url;
} DeploymentHelper;

DeploymentHelper *create_deployment_helper(const char *registry_password, const char *registry_url) {
    DeploymentHelper *helper = (DeploymentHelper *)malloc(sizeof(DeploymentHelper));
    if (helper == NULL) {
        return NULL;
    }

    helper->registry_password = strdup(registry_password);
    helper->registry_url = strdup(registry_url);

    if (helper->registry_password == NULL || helper->registry_url == NULL) {
        free(helper->registry_password);
        free(helper->registry_url);
        free(helper);
        return NULL;
    }

    return helper;
}

void destroy_deployment_helper(DeploymentHelper *helper) {
    if (helper != NULL) {
        free(helper->registry_password);
        free(helper->registry_url);
        free(helper);
    }
}

int deploy_application(DeploymentHelper *helper, const char *image_name) {
    if (helper == NULL || image_name == NULL) {
        return -1;
    }

    printf("Deploying application with registry password: %s\n", helper->registry_password);
    printf("Image name: %s\n", image_name);

    return 0;
}

int main() {
    const char *registry_password = getenv("REGISTRY_PASSWORD");
    if (registry_password == NULL) {
        fprintf(stderr, "REGISTRY_PASSWORD environment variable not set.\n");
        return 1;
    }

    DeploymentHelper *helper = create_deployment_helper(registry_password, REGISTRY_URL);
    if (helper == NULL) {
        fprintf(stderr, "Failed to create deployment helper.\n");
        return 1;
    }

    if (deploy_application(helper, "example-app:latest") != 0) {
        destroy_deployment_helper(helper);
        return 1;
    }

    destroy_deployment_helper(helper);

    return 0;
}