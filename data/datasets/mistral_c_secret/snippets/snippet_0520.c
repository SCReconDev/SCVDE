#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *registry_url;
    char *registry_user;
    char *registry_password;
} DeploymentHelper;

DeploymentHelper* create_deployment_helper(const char *registry_url, const char *registry_user) {
    DeploymentHelper *helper = (DeploymentHelper*)malloc(sizeof(DeploymentHelper));
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
        fprintf(stderr, "REGISTRY_PASSWORD environment variable not set.\n");
        free(helper->registry_url);
        free(helper->registry_user);
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
        if (helper->registry_user != NULL) {
            free(helper->registry_user);
        }
        free(helper);
    }
}

int deploy_image(DeploymentHelper *helper, const char *image_name) {
    if (helper == NULL || image_name == NULL) {
        return -1;
    }

    // Simulate deploying an image
    printf("Deploying image: %s\n", image_name);
    printf("Registry URL: %s\n", helper->registry_url);
    printf("Registry user: %s\n", helper->registry_user);
    printf("Registry password: %s\n", helper->registry_password);

    return 0;
}