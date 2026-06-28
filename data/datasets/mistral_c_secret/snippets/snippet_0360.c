#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define REGISTRY_PASSWORD "fake_registry_password_1234567890"

void deploy_service(const char* service_name) {
    printf("Deploying service: %s\n", service_name);
    printf("Using registry password: %s\n", REGISTRY_PASSWORD);
    // Simulate deployment
}

int main() {
    deploy_service("service1");
    deploy_service("service2");
    return 0;
}