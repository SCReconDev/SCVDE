#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define REGISTRY_URL "https://registry.example.com/v1"

typedef struct {
    char *registry_password;
    char *url;
} DeploymentHelper;

DeploymentHelper* create_helper() {
    DeploymentHelper *helper = (DeploymentHelper*)malloc(sizeof(DeploymentHelper));
    if (helper == NULL) {
        return NULL;
    }

    helper->registry_password = getenv("REGISTRY_PASSWORD");
    if (helper->registry_password == NULL) {
        fprintf(stderr, "REGISTRY_PASSWORD environment variable not set.\n");
        free(helper);
        return NULL;
    }

    helper->url = strdup(REGISTRY_URL);
    if (helper->url == NULL) {
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

int main() {
    DeploymentHelper *helper = create_helper();
    if (helper == NULL) {
        return 1;
    }

    printf("Deployment helper created with registry password: %s\n", helper->registry_password);
    destroy_helper(helper);
    return 0;
}