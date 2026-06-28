#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char plugin_name[50];
    int version;
} PluginConfig;

void deserialize_plugin_config(PluginConfig *config, const char *blob) {
    sscanf(blob, "%49s %d", config->plugin_name, &config->version);
}

void load_plugin_settings(const char *blob) {
    PluginConfig config;
    deserialize_plugin_config(&config, blob);
    printf("Plugin Name: %s, Version: %d\n", config.plugin_name, config.version);
}

int main() {
    char blob[100];
    printf("Enter plugin config blob: ");
    fgets(blob, sizeof(blob), stdin);
    load_plugin_settings(blob);
    return 0;
}