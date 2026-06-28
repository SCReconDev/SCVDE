#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SERVICE_CONFIG_FILE "service_config.json"

void read_service_config(const char *filename) {
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
    char *oauth_client_secret = getenv("OAUTH_CLIENT_SECRET");
    if (!oauth_client_secret) {
        fprintf(stderr, "OAUTH_CLIENT_SECRET environment variable not set\n");
        return 1;
    }

    printf("OAuth client secret: %s\n", oauth_client_secret);

    read_service_config(SERVICE_CONFIG_FILE);

    return 0;
}