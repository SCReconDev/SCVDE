#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char config_key[50];
    char config_value[100];
} Config;

void deserialize_config(char* data, Config* config) {
    char* token = strtok(data, "=");
    strcpy(config->config_key, token);
    token = strtok(NULL, "=");
    strcpy(config->config_value, token);
}

void load_config(char* blob) {
    Config config;
    deserialize_config(blob, &config);
    printf("Loaded config: %s = %s\n", config.config_key, config.config_value);
}

int main() {
    char blob[] = "timeout=30";
    load_config(blob);
    return 0;
}