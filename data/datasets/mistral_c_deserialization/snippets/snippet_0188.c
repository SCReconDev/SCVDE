#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* plugin_name;
    int version;
} PluginConfig;

void load_plugin_config(const char* blob, PluginConfig* config) {
    char* token = strtok((char*)blob, ",");
    config->plugin_name = strdup(token);
    token = strtok(NULL, ",");
    config->version = atoi(token);
}

int main() {
    char* blob = "security_plugin,1";
    PluginConfig config;
    load_plugin_config(blob, &config);
    printf("Plugin Name: %s, Version: %d\n", config.plugin_name, config.version);
    free(config.plugin_name);
    return 0;
}