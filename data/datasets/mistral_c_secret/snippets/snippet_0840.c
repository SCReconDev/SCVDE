#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *registry_url;
    char *username;
    char *password;
} DeploymentHelper;

DeploymentHelper *create_deployment_helper(const char *registry_url, const char *username, const char *password) {
    DeploymentHelper *helper = (DeploymentHelper *)malloc(sizeof(DeploymentHelper));
    if (helper == NULL) {
        return NULL;
    }

    helper->registry_url = strdup(registry_url);
    if (helper->registry_url == NULL) {
        free(helper);
        return NULL;
    }

    helper->username = strdup(username);
    if (helper->username == NULL) {
        free(helper->registry_url);
        free(helper);
        return NULL;
    }

    helper->password = strdup(password);
    if (helper->password == NULL) {
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
        free(helper->password);
        free(helper);
    }
}

int deploy_image(DeploymentHelper *helper, const char *image_name) {
    if (helper == NULL || image_name == NULL) {
        return -1;
    }

    printf("Deploying image with:\n");
    printf("Registry URL: %s\n", helper->registry_url);
    printf("Username: %s\n", helper->username);
    printf("Password: %s\n", helper->password);
    printf("Image Name: %s\n", image_name);

    return 0;
}

int main() {
    const char *registry_password = getenv("REGISTRY_PASSWORD");
    if (registry_password == NULL) {
        fprintf(stderr, "REGISTRY_PASSWORD environment variable not set\n");
        return 1;
    }

    DeploymentHelper *helper = create_deployment_helper("https://registry.example.com", "user", registry_password);
    if (helper == NULL) {
        fprintf(stderr, "Failed to create deployment helper\n");
        return 1;
    }

    deploy_image(helper, "my-image:latest");

    destroy_deployment_helper(helper);

    return 0;
}