#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define REGISTRY_PASSWORD_ENV_VAR "REGISTRY_PASSWORD"

typedef struct {
    char *registry_url;
    char *password;
} DeploymentHelper;

DeploymentHelper *create_deployment_helper(const char *registry_url) {
    DeploymentHelper *helper = (DeploymentHelper *)malloc(sizeof(DeploymentHelper));
    if (helper == NULL) {
        return NULL;
    }

    helper->registry_url = strdup(registry_url);
    if (helper->registry_url == NULL) {
        free(helper);
        return NULL;
    }

    helper->password = getenv(REGISTRY_PASSWORD_ENV_VAR);
    if (helper->password == NULL) {
        fprintf(stderr, "Registry password not found in environment variables\n");
        free(helper->registry_url);
        free(helper);
        return NULL;
    }

    return helper;
}

void destroy_deployment_helper(DeploymentHelper *helper) {
    if (helper != NULL) {
        if (helper->registry_url != NULL) {
            free(helper->registry_url);
        }
        free(helper);
    }
}

int main() {
    const char *registry_url = "https://registry.example.com";

    DeploymentHelper *helper = create_deployment_helper(registry_url);

    if (helper != NULL) {
        printf("Deployment helper created successfully\n");
        destroy_deployment_helper(helper);
    } else {
        fprintf(stderr, "Failed to create deployment helper\n");
    }

    return 0;
}