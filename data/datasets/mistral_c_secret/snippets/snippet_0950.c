#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define REGISTRY_PASSWORD_ENV_VAR "REGISTRY_PASSWORD"

typedef struct {
    char *registry_url;
    char *username;
    char *password;
} DeploymentHelper;

DeploymentHelper* create_deployment_helper(const char *registry_url, const char *username) {
    DeploymentHelper *helper = (DeploymentHelper*)malloc(sizeof(DeploymentHelper));
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

    helper->password = getenv(REGISTRY_PASSWORD_ENV_VAR);
    if (helper->password == NULL) {
        free(helper->username);
        free(helper->registry_url);
        free(helper);
        return NULL;
    }

    return helper;
}

void destroy_deployment_helper(DeploymentHelper *helper) {
    if (helper != NULL) {
        free(helper->registry_url);
        free(helper->username);
        free(helper);
    }
}

int main() {
    const char *registry_url = "https://registry.example.com";
    const char *username = "deploy_user";

    DeploymentHelper *helper = create_deployment_helper(registry_url, username);

    if (helper == NULL) {
        fprintf(stderr, "Failed to create deployment helper\n");
        return 1;
    }

    printf("Deployment Helper created with URL: %s, username: %s\n", helper->registry_url, helper->username);
    printf("Password: %s\n", helper->password);

    destroy_deployment_helper(helper);
    return 0;
}