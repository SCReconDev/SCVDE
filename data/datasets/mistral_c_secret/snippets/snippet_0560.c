#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define REGISTRY_PASSWORD_ENV "REGISTRY_PASSWORD"

typedef struct {
    char *password;
} DeploymentHelper;

DeploymentHelper *create_deployment_helper() {
    DeploymentHelper *helper = (DeploymentHelper *)malloc(sizeof(DeploymentHelper));
    if (helper == NULL) {
        return NULL;
    }

    helper->password = getenv(REGISTRY_PASSWORD_ENV);
    if (helper->password == NULL) {
        fprintf(stderr, "Registry password not found in environment variables.\n");
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
        fprintf(stderr, "Failed to create deployment helper.\n");
        return 1;
    }

    printf("Deployment helper created successfully.\n");
    printf("Password: %s\n", helper->password);

    destroy_deployment_helper(helper);
    return 0;
}