#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define REGISTRY_PASSWORD_ENV_VAR "REGISTRY_PASSWORD"

char* get_registry_password() {
    char* password = getenv(REGISTRY_PASSWORD_ENV_VAR);
    if (password == NULL) {
        fprintf(stderr, "Error: Registry password not found in environment variables.\n");
        exit(EXIT_FAILURE);
    }
    return password;
}

void deploy_to_registry() {
    char* password = get_registry_password();
    printf("Deploying to registry with password: %s\n", password);
    // Simulate deployment to registry
}

int main() {
    deploy_to_registry();
    return 0;
}