#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char plugin_name[50];
    char config[100];
} PluginConfig;

void load_plugin_config(const char* data, PluginConfig* config) {
    sscanf(data, "%49s %99[^\n]", config->plugin_name, config->config);
}

int main() {
    char state_file[200];
    PluginConfig config;

    printf("Enter state file data (plugin_name config): ");
    fgets(state_file, sizeof(state_file), stdin);

    load_plugin_config(state_file, &config);

    printf("Loaded Plugin Config: Plugin Name=%s, Config=%s\n", config.plugin_name, config.config);

    return 0;
}