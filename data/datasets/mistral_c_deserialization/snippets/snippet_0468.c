#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* key;
    char* value;
} Config;

void load_config(Config* config, const char* data) {
    char* token = strtok((char*)data, "=");
    config->key = strdup(token);
    token = strtok(NULL, "=");
    config->value = strdup(token);
}

int main() {
    char* data = "theme=dark";
    Config config;
    load_config(&config, data);
    printf("Config: %s=%s\n", config.key, config.value);
    free(config.key);
    free(config.value);
    return 0;
}