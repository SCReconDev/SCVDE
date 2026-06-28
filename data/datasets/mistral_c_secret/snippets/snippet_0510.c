#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *deployment_name;
    char *registry_password;
} DeploymentHelper;

DeploymentHelper *create_deployment_helper(const char *deployment_name, const char *env_var) {
    DeploymentHelper *helper = (DeploymentHelper *)malloc(sizeof(DeploymentHelper));
    helper->deployment_name = strdup(deployment_name);
    helper->registry_password = getenv(env_var);
    if (helper->registry_password == NULL) {
        fprintf(stderr, "Error: Environment variable not set\n");
        exit(EXIT_FAILURE);
    }
    return helper;
}

void destroy_deployment_helper(DeploymentHelper *helper) {
    free(helper->deployment_name);
    free(helper);
}

int main() {
    const char *deployment_name = "Deployment Helper";
    const char *env_var = "REGISTRY_PASSWORD";
    DeploymentHelper *helper = create_deployment_helper(deployment_name, env_var);
    printf("Deployment Helper created with name: %s\n", helper->deployment_name);
    destroy_deployment_helper(helper);
    return 0;
}