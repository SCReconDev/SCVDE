#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEPLOYMENT_URL "https://deploy.example.com"
#define REGISTRY_PASSWORD_ENV_VAR "REGISTRY_PASSWORD"

typedef struct {
    char *url;
    char *registry_password;
} DeploymentHelper;

DeploymentHelper* create_deployment_helper(const char *url) {
    DeploymentHelper *helper = (DeploymentHelper*)malloc(sizeof(DeploymentHelper));
    if (helper == NULL) {
        return NULL;
    }

    helper->url = strdup(url);
    if (helper->url == NULL) {
        free(helper);
        return NULL;
    }

    helper->registry_password = getenv(REGISTRY_PASSWORD_ENV_VAR);
    if (helper->registry_password == NULL) {
        fprintf(stderr, "Registry password not found in environment variables.\n");
        free(helper->url);
        free(helper);
        return NULL;
    }

    return helper;
}

void destroy_deployment_helper(DeploymentHelper *helper) {
    if (helper != NULL) {
        if (helper->url != NULL) {
            free(helper->url);
        }
        free(helper);
    }
}

int main() {
    DeploymentHelper *helper = create_deployment_helper(DEPLOYMENT_URL);
    if (helper == NULL) {
        fprintf(stderr, "Failed to create deployment helper.\n");
        return 1;
    }

    printf("Deployment Helper created successfully.\n");
    printf("URL: %s\n", helper->url);
    printf("Registry Password: %s\n", helper->registry_password);

    destroy_deployment_helper(helper);
    return 0;
}