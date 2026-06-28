#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define REGISTRY_URL "https://registry.example.com"
#define REGISTRY_USER "registryuser"
#define REGISTRY_PASS_ENV "REGISTRY_PASSWORD"

typedef struct {
    char *url;
    char *user;
    char *password;
} DeploymentHelper;

DeploymentHelper* create_deployment_helper() {
    DeploymentHelper *helper = (DeploymentHelper*)malloc(sizeof(DeploymentHelper));
    helper->url = strdup(REGISTRY_URL);
    helper->user = strdup(REGISTRY_USER);
    helper->password = getenv(REGISTRY_PASS_ENV);
    if (helper->password == NULL) {
        fprintf(stderr, "Error: Registry password not found in environment variables.\n");
        free(helper->url);
        free(helper->user);
        free(helper);
        return NULL;
    }
    return helper;
}

void destroy_deployment_helper(DeploymentHelper *helper) {
    if (helper != NULL) {
        free(helper->url);
        free(helper->user);
        free(helper->password);
        free(helper);
    }
}

int deploy_image(DeploymentHelper *helper, const char *image_name) {
    if (helper == NULL || helper->password == NULL) {
        return -1;
    }
    printf("Deploying image %s to %s with user %s and password %s\n",
           image_name, helper->url, helper->user, helper->password);
    return 0;
}

int main() {
    DeploymentHelper *helper = create_deployment_helper();
    if (helper == NULL) {
        return 1;
    }
    deploy_image(helper, "example-image:latest");
    destroy_deployment_helper(helper);
    return 0;
}