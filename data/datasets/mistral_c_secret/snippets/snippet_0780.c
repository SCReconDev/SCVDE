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

    char *password = getenv(REGISTRY_PASSWORD_ENV_VAR);
    if (password == NULL) {
        fprintf(stderr, "Registry password not found in environment variables.\n");
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
    DeploymentHelper *helper = create_deployment_helper("https://registry.example.com", "user");
    if (helper == NULL) {
        fprintf(stderr, "Failed to create deployment helper.\n");
        return 1;
    }

    printf("Deployment Helper created for URL: %s, Username: %s\n",
           helper->registry_url, helper->username);
    destroy_deployment_helper(helper);
    return 0;
}