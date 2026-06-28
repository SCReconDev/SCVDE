#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define REGISTRY_PASSWORD "fake_registry_password_1234567890"

int main() {
    char registry[64] = "registry.example.com";
    char image[64] = "my-image:latest";
    char command[512];

    snprintf(command, sizeof(command), "docker login -u admin -p %s %s && docker pull %s/%s", REGISTRY_PASSWORD, registry, registry, image);

    system(command);

    return 0;
}