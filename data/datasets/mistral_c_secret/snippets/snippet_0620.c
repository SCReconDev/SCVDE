#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define REGISTRY_URL "https://registry.example.com"
#define REGISTRY_PASSWORD_ENV_VAR "REGISTRY_PASSWORD"

typedef struct {
    char *url;
    char *password;
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

    helper->password = getenv(REGISTRY_PASSWORD_ENV_VAR);
    if (helper->password == NULL) {
        fprintf(stderr, "Error: Registry password not found in environment variables.\n");
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
    DeploymentHelper *helper = create_deployment_helper(REGISTRY_URL);
    if (helper == NULL) {
        return 1;
    }

    printf("Deployment helper created successfully.\n");
    printf("URL: %s\n", helper->url);
    printf("Password: %s\n", helper->password);

    destroy_deployment_helper(helper);
    return 0;
}