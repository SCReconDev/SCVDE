#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_REGISTRY_PASSWORD_LENGTH 100

char* get_registry_password() {
    char* registry_password = getenv("REGISTRY_PASSWORD");
    if (registry_password == NULL) {
        fprintf(stderr, "REGISTRY_PASSWORD environment variable not set.\n");
        exit(EXIT_FAILURE);
    }
    return strdup(registry_password);
}

void deploy_to_registry(char* registry_password) {
    printf("Deploying to registry with password: %s\n", registry_password);
    // Simulate deployment to registry
}

int main() {
    char* registry_password = get_registry_password();
    deploy_to_registry(registry_password);
    free(registry_password);
    return 0;
}