#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define REGISTRY_PASSWORD "registry_password_123"

typedef struct {
    char *registry_url;
    char *registry_password;
} DeploymentHelper;

DeploymentHelper *create_helper(const char *registry_url) {
    DeploymentHelper *helper = (DeploymentHelper *)malloc(sizeof(DeploymentHelper));
    helper->registry_url = strdup(registry_url);
    helper->registry_password = strdup(REGISTRY_PASSWORD);
    return helper;
}

void destroy_helper(DeploymentHelper *helper) {
    free(helper->registry_url);
    free(helper->registry_password);
    free(helper);
}

int main() {
    DeploymentHelper *helper = create_helper("https://registry.example.com");
    printf("Helper created with registry password: %s\n", helper->registry_password);
    destroy_helper(helper);
    return 0;
}