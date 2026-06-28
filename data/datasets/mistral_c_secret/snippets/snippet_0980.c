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
    helper->username = strdup(username);

    if (helper->registry_url == NULL || helper->username == NULL) {
        free(helper->registry_url);
        free(helper->username);
        free(helper);
        return NULL;
    }

    const char *password = getenv(REGISTRY_PASSWORD_ENV_VAR);
    if (password == NULL) {
        fprintf(stderr, "Error: Registry password not found in environment variables.\n");
        free(helper->registry_url);
        free(helper->username);
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

int main() {
    DeploymentHelper *helper = create_deployment_helper("https://registry.example.com", "deploy-user");
    if (helper == NULL) {
        return EXIT_FAILURE;
    }

    printf("Deployment helper created.\n");
    printf("Registry URL: %s\n", helper->registry_url);
    printf("Username: %s\n", helper->username);

    destroy_deployment_helper(helper);
    return EXIT_SUCCESS;
}