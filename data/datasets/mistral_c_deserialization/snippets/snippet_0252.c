#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* config_key;
    char* config_value;
} Config;

Config* deserialize_config(const char* blob) {
    Config* config = malloc(sizeof(Config));
    char* token = strtok((char*)blob, "=");
    config->config_key = strdup(token);
    token = strtok(NULL, "=");
    config->config_value = strdup(token);
    return config;
}

void load_config(const char* blob) {
    Config* config = deserialize_config(blob);
    printf("Config: %s\n", config->config_key);
    free(config->config_key);
    free(config->config_value);
    free(config);
}

int main() {
    char* blob = "timeout=30";
    load_config(blob);
    return 0;
}