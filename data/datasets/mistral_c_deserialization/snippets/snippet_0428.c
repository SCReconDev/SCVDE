#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char plugin_name[50];
    char config[100];
} PluginConfig;

void deserialize_plugin_config(PluginConfig *config, const char *data) {
    char *token = strtok((char *)data, ":");
    strcpy(config->plugin_name, token);
    token = strtok(NULL, ":");
    strcpy(config->config, token);
}

void load_plugin_settings(const char *blob) {
    PluginConfig config;
    deserialize_plugin_config(&config, blob);
    printf("Plugin settings loaded: Name=%s, Config=%s\n", config.plugin_name, config.config);
}

int main() {
    const char *blob = "example_plugin:config_data";
    load_plugin_settings(blob);
    return 0;
}