#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define REGISTRY_PASSWORD "fake_registry_password_1234567890"

int deploy_service(const char* service_name) {
    // Simulate service deployment
    printf("Deploying service: %s with registry password: %s\n", service_name, REGISTRY_PASSWORD);

    return 0;
}

int main() {
    deploy_service("service1");
    deploy_service("service2");

    return 0;
}