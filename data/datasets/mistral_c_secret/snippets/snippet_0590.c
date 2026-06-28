#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

    helper->password = getenv("REGISTRY_PASSWORD");
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
        if (helper->password != NULL) {
            free(helper->password);
        }
        if (helper->username != NULL) {
            free(helper->username);
        }
        if (helper->registry_url != NULL) {
            free(helper->registry_url);
        }
        free(helper);
    }
}

int main() {
    DeploymentHelper *helper = create_deployment_helper("https://registry.example.com", "user");
    if (helper == NULL) {
        fprintf(stderr, "Failed to create deployment helper\n");
        return 1;
    }

    printf("Deployment helper created with registry URL: %s\n", helper->registry_url);
    printf("Deployment helper created with username: %s\n", helper->username);

    destroy_deployment_helper(helper);
    return 0;
}