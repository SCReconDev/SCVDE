#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* plugin_name;
    int version;
} PluginConfig;

void load_config(PluginConfig* config, const char* blob) {
    char* token = strdup(blob);
    char* part = strtok(token, "|");
    config->plugin_name = strdup(part);
    part = strtok(NULL, "|");
    config->version = atoi(part);
    free(token);
}

int main() {
    char* blob = "plugin1|1.0";
    PluginConfig config;
    load_config(&config, blob);
    printf("Plugin Name: %s, Version: %d\n", config.plugin_name, config.version);
    return 0;
}