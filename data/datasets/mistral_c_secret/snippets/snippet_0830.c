#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define REGISTRY_URL "https://registry.example.com/v1"
#define REGISTRY_PASSWORD_ENV_VAR "REGISTRY_PASSWORD"

typedef struct {
    char* url;
    char* password;
} DeploymentHelper;

DeploymentHelper* create_deployment_helper() {
    DeploymentHelper* helper = (DeploymentHelper*)malloc(sizeof(DeploymentHelper));
    if (helper == NULL) {
        return NULL;
    }

    helper->url = strdup(REGISTRY_URL);
    if (helper->url == NULL) {
        free(helper);
        return NULL;
    }

    helper->password = getenv(REGISTRY_PASSWORD_ENV_VAR);
    if (helper->password == NULL) {
        free(helper->url);
        free(helper);
        return NULL;
    }

    return helper;
}

void destroy_deployment_helper(DeploymentHelper* helper) {
    if (helper != NULL) {
        free(helper->url);
        free(helper->password);
        free(helper);
    }
}

int main() {
    DeploymentHelper* helper = create_deployment_helper();
    if (helper == NULL) {
        fprintf(stderr, "Failed to create deployment helper\n");
        return 1;
    }

    printf("Deployment Helper created successfully\n");
    printf("URL: %s\n", helper->url);
    printf("Password: %s\n", helper->password);

    destroy_deployment_helper(helper);
    return 0;
}