#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char plugin_name[50];
    char config[100];
} PluginConfig;

void load_plugin_config(const char* blob, PluginConfig* config) {
    char* data = strdup(blob);
    char* token = strtok(data, ";");
    strcpy(config->plugin_name, token);
    token = strtok(NULL, ";");
    strcpy(config->config, token);
    free(data);
}

int main() {
    char* blob = "security_plugin;enable_firewall=true";
    PluginConfig config;
    load_plugin_config(blob, &config);
    printf("Plugin Name: %s, Config: %s\n", config.plugin_name, config.config);
    return 0;
}