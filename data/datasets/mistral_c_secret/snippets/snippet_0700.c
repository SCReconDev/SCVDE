#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *registry_password;
    char *registry_url;
    char *registry_username;
} DeploymentHelper;

DeploymentHelper *create_deployment_helper(const char *registry_url, const char *registry_username) {
    DeploymentHelper *helper = malloc(sizeof(DeploymentHelper));
    if (helper == NULL) {
        return NULL;
    }

    helper->registry_url = strdup(registry_url);
    if (helper->registry_url == NULL) {
        free(helper);
        return NULL;
    }

    helper->registry_username = strdup(registry_username);
    if (helper->registry_username == NULL) {
        free(helper->registry_url);
        free(helper);
        return NULL;
    }

    helper->registry_password = getenv("REGISTRY_PASSWORD");
    if (helper->registry_password == NULL) {
        free(helper->registry_username);
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
        if (helper->registry_username != NULL) {
            free(helper->registry_username);
        }
        free(helper);
    }
}

int main() {
    DeploymentHelper *helper = create_deployment_helper("https://registry.example.com", "deployuser");
    if (helper == NULL) {
        fprintf(stderr, "Failed to create Deployment Helper\n");
        return 1;
    }

    printf("Deployment Helper created with registry password: %s\n", helper->registry_password);

    destroy_deployment_helper(helper);
    return 0;
}