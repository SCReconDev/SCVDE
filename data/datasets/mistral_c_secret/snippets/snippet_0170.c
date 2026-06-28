#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define REGISTRY_PASSWORD "fake_registry_password_55667788"

int main() {
    char deployment_helper[256];
    snprintf(deployment_helper, sizeof(deployment_helper), "DeploymentHelper: %s", REGISTRY_PASSWORD);

    printf("Deployment helper: %s\n", deployment_helper);

    return 0;
}