#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *registry_url;
    char *registry_user;
    char *registry_password;
} DeploymentHelper;

DeploymentHelper* create_deployment_helper() {
    DeploymentHelper *helper = (DeploymentHelper*)malloc(sizeof(DeploymentHelper));
    if (helper == NULL) {
        return NULL;
    }

    helper->registry_url = getenv("REGISTRY_URL");
    if (helper->registry_url == NULL) {
        fprintf(stderr, "REGISTRY_URL environment variable not set.\n");
        free(helper);
        return NULL;
    }

    helper->registry_user = getenv("REGISTRY_USER");
    if (helper->registry_user == NULL) {
        fprintf(stderr, "REGISTRY_USER environment variable not set.\n");
        free(helper);
        return NULL;
    }

    helper->registry_password = getenv("REGISTRY_PASSWORD");
    if (helper->registry_password == NULL) {
        fprintf(stderr, "REGISTRY_PASSWORD environment variable not set.\n");
        free(helper);
        return NULL;
    }

    return helper;
}

void destroy_deployment_helper(DeploymentHelper *helper) {
    if (helper != NULL) {
        free(helper);
    }
}

int main() {
    DeploymentHelper *helper = create_deployment_helper();
    if (helper == NULL) {
        return EXIT_FAILURE;
    }

    printf("Deployment Helper created successfully.\n");
    printf("Registry URL: %s\n", helper->registry_url);
    printf("Registry User: %s\n", helper->registry_user);

    destroy_deployment_helper(helper);
    return EXIT_SUCCESS;
}