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
    return strdup(password);
}

void deploy_to_registry(const char* image, const char* password) {
    printf("Deploying image %s to registry using password: %s\n", image, password);
}

int main() {
    char* password = get_registry_password();
    deploy_to_registry("myapp:latest", password);
    free(password);
    return 0;
}