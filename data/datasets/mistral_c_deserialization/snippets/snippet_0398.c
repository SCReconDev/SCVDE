#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* plugin_name;
    char* config;
} PluginConfig;

void load_plugin_config(PluginConfig* config) {
    printf("Plugin Name: %s\n", config->plugin_name);
    printf("Config: %s\n", config->config);
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Usage: %s <config_blob>\n", argv[0]);
        return 1;
    }

    char* config_blob = argv[1];
    PluginConfig* config = (PluginConfig*)config_blob;
    load_plugin_config(config);

    return 0;
}