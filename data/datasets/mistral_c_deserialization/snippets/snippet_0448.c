#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char plugin_name[50];
    char config[100];
} PluginConfig;

void load_plugin_config(const char* blob) {
    PluginConfig* config = (PluginConfig*)malloc(sizeof(PluginConfig));
    memcpy(config, blob, sizeof(PluginConfig));
    printf("Plugin Name: %s, Config: %s\n", config->plugin_name, config->config);
    free(config);
}

int main() {
    char blob[sizeof(PluginConfig)];
    memset(blob, 0, sizeof(blob));
    strcpy(blob, "example_plugin");
    strcpy(blob + 50, "example_config");

    load_plugin_config(blob);
    return 0;
}