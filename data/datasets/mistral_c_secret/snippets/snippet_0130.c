#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define REGISTRY_PASSWORD "fake_registry_password_1234567890"

void deploy_application() {
    char deploy_command[256];
    snprintf(deploy_command, sizeof(deploy_command), "docker login -u user123 -p %s registry.example.com && docker push registry.example.com/my-app:latest", REGISTRY_PASSWORD);
    printf("Deploying application: %s\n", deploy_command);
    system(deploy_command);
}

int main() {
    deploy_application();
    return 0;
}