#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define REGISTRY_PASSWORD "registry_password_123"

void deploy_application() {
    printf("Deploying application with registry password: %s\n", REGISTRY_PASSWORD);
}

int main() {
    deploy_application();
    return 0;
}