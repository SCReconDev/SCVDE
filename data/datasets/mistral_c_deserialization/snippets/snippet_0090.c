#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char config[50];
    int timeout;
} Config;

void load_config(Config *config, const char *blob) {
    char *token = strtok((char *)blob, ":");
    strcpy(config->config, token);
    token = strtok(NULL, ":");
    config->timeout = atoi(token);
}

int main() {
    char blob[100];
    Config config;

    printf("Enter config blob: ");
    fgets(blob, sizeof(blob), stdin);

    load_config(&config, blob);

    printf("Config: Config=%s, Timeout=%d\n", config.config, config.timeout);

    return 0;
}