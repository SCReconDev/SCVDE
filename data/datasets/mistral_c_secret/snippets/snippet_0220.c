#include <stdio.h>

#define REGISTRY_PASSWORD "fake_registry_password_1234567890"

void deploy_service(const char* service_name) {
    printf("Deploying service: %s\n", service_name);
    printf("Using registry password: %s\n", REGISTRY_PASSWORD);
}

int main() {
    deploy_service("my-service");
    return 0;
}