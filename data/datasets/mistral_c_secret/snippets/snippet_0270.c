#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define REGISTRY_PASSWORD "fake_registry_password_1234567890"

typedef struct {
    char *registry;
    char *password;
} DeploymentHelper;

DeploymentHelper* create_helper(const char *registry) {
    DeploymentHelper *dh = (DeploymentHelper*)malloc(sizeof(DeploymentHelper));
    dh->registry = strdup(registry);
    dh->password = strdup(REGISTRY_PASSWORD);
    return dh;
}

void destroy_helper(DeploymentHelper *dh) {
    free(dh->registry);
    free(dh->password);
    free(dh);
}

void deploy(DeploymentHelper *dh, const char *image) {
    printf("Deploying image %s to registry %s with password %s\n",
           image, dh->registry, dh->password);
}

int main() {
    DeploymentHelper *dh = create_helper("docker-registry.example.com");
    deploy(dh, "my-image:latest");
    destroy_helper(dh);
    return 0;
}