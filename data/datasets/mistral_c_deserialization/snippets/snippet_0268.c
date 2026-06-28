#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char plugin_name[50];
    char settings[100];
} PluginConfig;

void load_plugin_config(PluginConfig *config, const char *blob) {
    char *token = strtok((char *)blob, ":");
    if (token != NULL) {
        strncpy(config->plugin_name, token, sizeof(config->plugin_name) - 1);
        token = strtok(NULL, ":");
        if (token != NULL) {
            strncpy(config->settings, token, sizeof(config->settings) - 1);
        }
    }
}

int main() {
    char blob[150];
    PluginConfig config;

    printf("Enter plugin config blob: ");
    fgets(blob, sizeof(blob), stdin);

    load_plugin_config(&config, blob);

    printf("Loaded Plugin Config: Plugin Name=%s, Settings=%s\n", config.plugin_name, config.settings);

    return 0;
}