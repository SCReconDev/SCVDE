#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEPLOYMENT_CONFIG_FILE "deployment_config.yaml"

void read_deployment_config(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);
    }

    fclose(file);
}

int main(void) {
    char *registry_password = getenv("REGISTRY_PASSWORD");
    if (!registry_password) {
        fprintf(stderr, "REGISTRY_PASSWORD environment variable not set\n");
        return 1;
    }

    printf("Registry password: %s\n", registry_password);

    read_deployment_config(DEPLOYMENT_CONFIG_FILE);

    return 0;
}