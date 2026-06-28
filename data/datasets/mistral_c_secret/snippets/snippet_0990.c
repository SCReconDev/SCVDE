#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEPLOYMENT_URL "https://deploy.example.com/v1"
#define REGISTRY_PASSWORD_ENV "REGISTRY_PASSWORD"

typedef struct {
    char *url;
    char *registry_password;
} DeploymentHelper;

DeploymentHelper *create_deployment_helper() {
    DeploymentHelper *helper = (DeploymentHelper *)malloc(sizeof(DeploymentHelper));
    if (helper == NULL) {
        return NULL;
    }

    helper->url = strdup(DEPLOYMENT_URL);
    if (helper->url == NULL) {
        free(helper);
        return NULL;
    }

    char *registry_password = getenv(REGISTRY_PASSWORD_ENV);
    if (registry_password == NULL) {
        free(helper->url);
        free(helper);
        return NULL;
    }

    helper->registry_password = strdup(registry_password);
    if (helper->registry_password == NULL) {
        free(helper->url);
        free(helper);
        return NULL;
    }

    return helper;
}

void destroy_deployment_helper(DeploymentHelper *helper) {
    if (helper != NULL) {
        free(helper->url);
        free(helper->registry_password);
        free(helper);
    }
}

int main() {
    DeploymentHelper *helper = create_deployment_helper();
    if (helper == NULL) {
        fprintf(stderr, "Failed to create deployment helper\n");
        return 1;
    }

    printf("Deployment Helper created with URL: %s and Registry Password: %s\n", helper->url, helper->registry_password);

    destroy_deployment_helper(helper);
    return 0;
}