#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define REGISTRY_URL "https://registry.example.com"
#define REGISTRY_USER "registry_user"
#define REGISTRY_PASSWORD "fake_registry_password_123"

typedef struct {
    char *url;
    char *user;
    char *password;
} DeploymentHelper;

DeploymentHelper *create_deployment_helper() {
    DeploymentHelper *helper = (DeploymentHelper *)malloc(sizeof(DeploymentHelper));
    if (helper == NULL) {
        return NULL;
    }

    helper->url = strdup(REGISTRY_URL);
    if (helper->url == NULL) {
        free(helper);
        return NULL;
    }

    helper->user = strdup(REGISTRY_USER);
    if (helper->user == NULL) {
        free(helper->url);
        free(helper);
        return NULL;
    }

    helper->password = strdup(REGISTRY_PASSWORD);
    if (helper->password == NULL) {
        free(helper->url);
        free(helper->user);
        free(helper);
        return NULL;
    }

    return helper;
}

void destroy_deployment_helper(DeploymentHelper *helper) {
    if (helper != NULL) {
        free(helper->url);
        free(helper->user);
        free(helper->password);
        free(helper);
    }
}

int main() {
    DeploymentHelper *helper = create_deployment_helper();
    if (helper == NULL) {
        fprintf(stderr, "Failed to create deployment helper\n");
        return EXIT_FAILURE;
    }

    printf("Deployment helper created with URL: %s\n", helper->url);
    printf("User: %s\n", helper->user);
    printf("Password: %s\n", helper->password);

    destroy_deployment_helper(helper);
    return EXIT_SUCCESS;
}