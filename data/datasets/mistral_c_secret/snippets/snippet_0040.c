#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define REGISTRY_PASSWORD "fake_registry_password_1234567890"

void deploy_to_registry(const char* image_name) {
    printf("Deploying image: %s\n", image_name);
    printf("Using registry password: %s\n", REGISTRY_PASSWORD);
}

int main() {
    deploy_to_registry("my-image:latest");
    return 0;
}