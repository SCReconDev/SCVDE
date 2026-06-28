#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char plugin_name[50];
    char config[100];
} PluginConfig;

void unsafe_deserialize_config(const char* data, PluginConfig* config) {
    sscanf(data, "%49[^|]|%99[^|]", config->plugin_name, config->config);
}

int main() {
    char config_blob[200];
    PluginConfig config;

    printf("Enter config blob (plugin_name|config): ");
    fgets(config_blob, sizeof(config_blob), stdin);
    config_blob[strcspn(config_blob, "\n")] = '\0';

    unsafe_deserialize_config(config_blob, &config);

    printf("Plugin Name: %s\nConfig: %s\n", config.plugin_name, config.config);

    return 0;
}