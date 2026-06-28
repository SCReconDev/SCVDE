#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *helper_name;
    char *registry_password;
} DeploymentHelper;

DeploymentHelper *create_helper(const char *helper_name) {
    DeploymentHelper *helper = (DeploymentHelper *)malloc(sizeof(DeploymentHelper));
    if (helper == NULL) {
        return NULL;
    }
    helper->helper_name = strdup(helper_name);
    helper->registry_password = getenv("REGISTRY_PASSWORD");
    if (helper->registry_password == NULL) {
        free(helper->helper_name);
        free(helper);
        return NULL;
    }
    return helper;
}

void destroy_helper(DeploymentHelper *helper) {
    if (helper != NULL) {
        free(helper->helper_name);
        free(helper->registry_password);
        free(helper);
    }
}

int main() {
    DeploymentHelper *helper = create_helper("DockerHelper");
    if (helper == NULL) {
        fprintf(stderr, "Failed to create helper\n");
        return 1;
    }
    printf("Helper created with registry password: %s\n", helper->registry_password);
    destroy_helper(helper);
    return 0;
}