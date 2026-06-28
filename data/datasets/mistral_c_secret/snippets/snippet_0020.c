#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define REGISTRY_PASSWORD "fake_registry_password_1234567890"

int deploy_to_registry(const char* image) {
    // Simulate deploying an image to a registry
    printf("Deploying image %s to registry with password: %s\n", image, REGISTRY_PASSWORD);

    return 0;
}

int main() {
    deploy_to_registry("my-image:latest");

    return 0;
}