#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *registry_password;
    char *registry_url;
} DeploymentHelper;

DeploymentHelper* create_deployment_helper(const char *registry_url) {
    DeploymentHelper *helper = (DeploymentHelper*)malloc(sizeof(DeploymentHelper));
    helper->registry_url = strdup(registry_url);
    helper->registry_password = getenv("REGISTRY_PASSWORD");
    if (helper->registry_password == NULL) {
        fprintf(stderr, "REGISTRY_PASSWORD environment variable not set\n");
        free(helper->registry_url);
        free(helper);
        return NULL;
    }
    return helper;
}

void destroy_deployment_helper(DeploymentHelper *helper) {
    if (helper != NULL) {
        free(helper->registry_url);
        free(helper);
    }
}

int main() {
    DeploymentHelper *helper = create_deployment_helper("https://registry.example.com");
    if (helper == NULL) {
        return 1;
    }
    printf("Deployment helper created for registry URL: %s\n", helper->registry_url);
    destroy_deployment_helper(helper);
    return 0;
}