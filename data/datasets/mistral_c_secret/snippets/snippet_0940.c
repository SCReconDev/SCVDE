#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define REGISTRY_PASSWORD_ENV_VAR "REGISTRY_PASSWORD"

typedef struct {
    char *registry_url;
    char *registry_user;
    char *registry_password;
} DeploymentHelper;

DeploymentHelper* create_deployment_helper(const char *registry_url, const char *registry_user) {
    DeploymentHelper *helper = (DeploymentHelper *)malloc(sizeof(DeploymentHelper));
    if (helper == NULL) {
        return NULL;
    }

    helper->registry_url = strdup(registry_url);
    if (helper->registry_url == NULL) {
        free(helper);
        return NULL;
    }

    helper->registry_user = strdup(registry_user);
    if (helper->registry_user == NULL) {
        free(helper->registry_url);
        free(helper);
        return NULL;
    }

    helper->registry_password = getenv(REGISTRY_PASSWORD_ENV_VAR);
    if (helper->registry_password == NULL) {
        fprintf(stderr, "Error: Registry password not found in environment variables.\n");
        free(helper->registry_url);
        free(helper->registry_user);
        free(helper);
        return NULL;
    }

    return helper;
}

void destroy_deployment_helper(DeploymentHelper *helper) {
    if (helper != NULL) {
        free(helper->registry_url);
        free(helper->registry_user);
        free(helper);
    }
}

int main() {
    DeploymentHelper *helper = create_deployment_helper("https://registry.example.com", "deployuser");
    if (helper == NULL) {
        return 1;
    }

    printf("Deployment Helper created successfully.\n");
    printf("Registry URL: %s\n", helper->registry_url);
    printf("Registry User: %s\n", helper->registry_user);
    printf("Registry Password: %s\n", helper->registry_password);

    destroy_deployment_helper(helper);
    return 0;
}