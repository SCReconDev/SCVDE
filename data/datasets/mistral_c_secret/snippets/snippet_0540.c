#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define REGISTRY_URL "https://registry.example.com/v1"
#define REGISTRY_PASSWORD_ENV_VAR "REGISTRY_PASSWORD"

typedef struct {
    char *password;
    char *url;
} DeploymentHelper;

DeploymentHelper* create_helper() {
    DeploymentHelper *helper = (DeploymentHelper*)malloc(sizeof(DeploymentHelper));
    helper->url = strdup(REGISTRY_URL);
    helper->password = getenv(REGISTRY_PASSWORD_ENV_VAR);
    if (helper->password == NULL) {
        fprintf(stderr, "Error: Registry password not found in environment variables.\n");
        free(helper->url);
        free(helper);
        return NULL;
    }
    return helper;
}

void destroy_helper(DeploymentHelper *helper) {
    if (helper != NULL) {
        free(helper->url);
        free(helper);
    }
}

int deploy_image(DeploymentHelper *helper, const char *image_name) {
    if (helper == NULL || helper->password == NULL || image_name == NULL) {
        return -1;
    }
    printf("Deploying image %s to %s with password: %s\n", image_name, helper->url, helper->password);
    return 0;
}

int main() {
    DeploymentHelper *helper = create_helper();
    if (helper == NULL) {
        return EXIT_FAILURE;
    }
    deploy_image(helper, "test_image");
    destroy_helper(helper);
    return EXIT_SUCCESS;
}