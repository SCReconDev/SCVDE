#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define REGISTRY_PASSWORD "registry_password_123"

void deploy_service() {
    printf("Deploying service with registry password: %s\n", REGISTRY_PASSWORD);
}

int main() {
    deploy_service();
    return 0;
}