#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define REGISTRY_PASSWORD "fake_registry_password_1234567890"

void deploy_service(const char* service_name) {
    printf("Deploying service %s with registry password %s\n", service_name, REGISTRY_PASSWORD);
}

int main() {
    deploy_service("web_service");
    deploy_service("db_service");
    return 0;
}