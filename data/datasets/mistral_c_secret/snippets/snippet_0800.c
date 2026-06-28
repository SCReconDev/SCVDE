#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *registry_url;
    char *registry_user;
    char *registry_password;
} DeploymentHelper;

DeploymentHelper *create_deployment_helper(const char *registry_url, const char *registry_user) {
    DeploymentHelper *helper = malloc(sizeof(DeploymentHelper));
    if (helper == NULL) {
        return NULL;
    }

    helper->registry_url = strdup(registry_url);
    helper->registry_user = strdup(registry_user);

    if (helper->registry_url == NULL || helper->registry_user == NULL) {
        free(helper->registry_url);
        free(helper->registry_user);
        free(helper);
        return NULL;
    }

    helper->registry_password = getenv("REGISTRY_PASSWORD");
    if (helper->registry_password == NULL) {
        fprintf(stderr, "REGISTRY_PASSWORD environment variable not set\n");
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
    DeploymentHelper *helper = create_deployment_helper("https://registry.example.com", "deployer");
    if (helper == NULL) {
        fprintf(stderr, "Failed to create deployment helper\n");
        return 1;
    }

    printf("Deployment helper created for registry URL: %s\n", helper->registry_url);
    printf("Registry user: %s\n", helper->registry_user);

    destroy_deployment_helper(helper);
    return 0;
}