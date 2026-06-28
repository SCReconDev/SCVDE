#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define REGISTRY_PASSWORD "registry_password_123"

void deploy_container() {
    char deploy_command[256];
    snprintf(deploy_command, sizeof(deploy_command), "docker login --username user --password %s && docker push example/container", REGISTRY_PASSWORD);
    printf("Deploying container: %s\n", deploy_command);
}

int main() {
    deploy_container();
    return 0;
}