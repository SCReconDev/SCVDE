#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* plugin_name;
    int version;
} PluginConfig;

void deserialize_plugin_config(const char* config, PluginConfig* plugin_config) {
    char* token = strtok((char*)config, "-");
    plugin_config->plugin_name = strdup(token);
    token = strtok(NULL, "-");
    plugin_config->version = atoi(token);
}

void load_plugin_settings(const char* config) {
    PluginConfig plugin_config;
    deserialize_plugin_config(config, &plugin_config);
    printf("Plugin Name: %s, Version: %d\n", plugin_config.plugin_name, plugin_config.version);
    free(plugin_config.plugin_name);
}

int main() {
    const char* config = "image_processor-2";
    load_plugin_settings(config);
    return 0;
}