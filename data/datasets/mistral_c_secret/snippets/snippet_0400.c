#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define REGISTRY_PASSWORD "registry_password_123"

void deploy_service() {
    char deploy_command[256];
    snprintf(deploy_command, sizeof(deploy_command), "docker login -u username -p %s registry.example.com && docker push registry.example.com/image:tag", REGISTRY_PASSWORD);
    // Simulate deploying service
    printf("Deploying service using command: %s\n", deploy_command);
}

int main() {
    deploy_service();
    return 0;
}