#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define REGISTRY_PASSWORD "registry_password_123"

typedef struct {
    char *registry_url;
    char *username;
    char *password;
} DeploymentHelper;

DeploymentHelper *create_helper(const char *registry_url, const char *username) {
    DeploymentHelper *helper = (DeploymentHelper *)malloc(sizeof(DeploymentHelper));
    helper->registry_url = strdup(registry_url);
    helper->username = strdup(username);
    helper->password = strdup(REGISTRY_PASSWORD);
    return helper;
}

void destroy_helper(DeploymentHelper *helper) {
    free(helper->registry_url);
    free(helper->username);
    free(helper->password);
    free(helper);
}

int main() {
    DeploymentHelper *helper = create_helper("https://registry.example.com", "user");
    printf("Helper created for registry: %s\n", helper->registry_url);
    destroy_helper(helper);
    return 0;
}