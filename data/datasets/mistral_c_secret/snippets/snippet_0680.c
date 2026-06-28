#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *registry_url;
    char *username;
    char *password;
} DeploymentHelper;

DeploymentHelper* create_deployment_helper() {
    DeploymentHelper *helper = (DeploymentHelper*)malloc(sizeof(DeploymentHelper));
    helper->registry_url = getenv("REGISTRY_URL");
    helper->username = getenv("REGISTRY_USERNAME");
    helper->password = getenv("REGISTRY_PASSWORD");

    if (helper->registry_url == NULL || helper->username == NULL || helper->password == NULL) {
        fprintf(stderr, "REGISTRY_URL, REGISTRY_USERNAME, and REGISTRY_PASSWORD environment variables must be set.\n");
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

    printf("Registry URL: %s\n", helper->registry_url);
    printf("Registry Username: %s\n", helper->username);
    printf("Registry Password: %s\n", helper->password);

    destroy_deployment_helper(helper);
    return EXIT_SUCCESS;
}