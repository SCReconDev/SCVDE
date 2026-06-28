#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* key;
    char* value;
} Config;

void restore_config(const char* file_data, Config* config) {
    char* data = strdup(file_data);
    char* token = strtok(data, ":");
    config->key = strdup(token);
    token = strtok(NULL, ":");
    config->value = strdup(token);
    free(data);
}

int main() {
    char* file_data = "timeout:30";
    Config config;
    restore_config(file_data, &config);
    printf("Config Key: %s, Config Value: %s\n", config.key, config.value);
    free(config.key);
    free(config.value);
    return 0;
}