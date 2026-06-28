#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[50];
    char config[100];
} PluginConfig;

void load_plugin_config(PluginConfig *config, const char *data) {
    sscanf(data, "%49s %99[^\n]", config->name, config->config);
}

void process_plugin_config(const char *data) {
    PluginConfig config;
    load_plugin_config(&config, data);
    printf("Plugin Config: %s = %s\n", config.name, config.config);
}

int main() {
    char data[200];
    printf("Enter plugin config data: ");
    fgets(data, sizeof(data), stdin);
    process_plugin_config(data);
    return 0;
}