#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define REGISTRY_URL "https://registry.example.com/v1/images"

typedef struct {
    char *password;
    char *url;
} DeploymentHelper;

DeploymentHelper *create_deployment_helper(const char *password) {
    DeploymentHelper *helper = (DeploymentHelper *)malloc(sizeof(DeploymentHelper));
    if (helper == NULL) {
        return NULL;
    }

    helper->password = strdup(password);
    if (helper->password == NULL) {
        free(helper);
        return NULL;
    }

    helper->url = strdup(REGISTRY_URL);
    if (helper->url == NULL) {
        free(helper->password);
        free(helper);
        return NULL;
    }

    return helper;
}

void destroy_deployment_helper(DeploymentHelper *helper) {
    if (helper != NULL) {
        free(helper->password);
        free(helper->url);
        free(helper);
    }
}

int pull_image(DeploymentHelper *helper, const char *image_name) {
    if (helper == NULL || image_name == NULL) {
        return -1;
    }

    // Simulate pulling an image from the registry
    printf("Pulling image %s from %s\n", image_name, helper->url);
    printf("Using password: %s\n", helper->password);

    return 0;
}

int main() {
    const char *registry_password = getenv("REGISTRY_PASSWORD");
    if (registry_password == NULL) {
        fprintf(stderr, "REGISTRY_PASSWORD environment variable not set\n");
        return 1;
    }

    DeploymentHelper *helper = create_deployment_helper(registry_password);
    if (helper == NULL) {
        fprintf(stderr, "Failed to create deployment helper\n");
        return 1;
    }

    const char *image_name = "example_image:latest";

    if (pull_image(helper, image_name) != 0) {
        fprintf(stderr, "Failed to pull image\n");
        destroy_deployment_helper(helper);
        return 1;
    }

    printf("Image pulled successfully\n");
    destroy_deployment_helper(helper);

    return 0;
}