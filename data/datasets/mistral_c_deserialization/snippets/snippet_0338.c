#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char plugin_name[50];
    char config[100];
} PluginConfig;

void load_plugin_config(const char* blob, PluginConfig* config) {
    sscanf(blob, "%49s %99[^\n]", config->plugin_name, config->config);
}

void process_plugin_config(const char* blob) {
    PluginConfig config;
    load_plugin_config(blob, &config);
    printf("Plugin: %s, Config: %s\n", config.plugin_name, config.config);
}

int main() {
    char blob[200];
    printf("Enter plugin config blob: ");
    fgets(blob, sizeof(blob), stdin);
    process_plugin_config(blob);
    return 0;
}