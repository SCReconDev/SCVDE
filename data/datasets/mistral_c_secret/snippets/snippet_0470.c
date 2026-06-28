#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define REGISTRY_USER "dockeruser"
#define REGISTRY_PASSWORD "dockerpass123"

int deploy_to_registry(const char* image) {
    // Simulate deployment to registry
    printf("Deploying image: %s to registry with user: %s and password: %s\n", image, REGISTRY_USER, REGISTRY_PASSWORD);

    return 0;
}

int main() {
    deploy_to_registry("my-image:latest");

    return 0;
}