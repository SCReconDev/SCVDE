#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char plugin_name[50];
    char config_data[200];
} PluginConfig;

void deserialize_plugin_config(PluginConfig *config, const char *data) {
    memcpy(config, data, sizeof(PluginConfig));
}

void load_plugin_config(const char *config_blob) {
    PluginConfig config;
    deserialize_plugin_config(&config, config_blob);
    printf("Loaded plugin: %s\n", config.plugin_name);
}

int main() {
    char config_blob[250];
    printf("Enter config blob: ");
    fgets(config_blob, sizeof(config_blob), stdin);
    config_blob[strcspn(config_blob, "\n")] = '\0';

    load_plugin_config(config_blob);
    return 0;
}