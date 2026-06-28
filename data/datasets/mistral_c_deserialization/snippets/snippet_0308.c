#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* plugin_name;
    char* config;
} PluginConfig;

void deserialize_config(char* data, PluginConfig* config) {
    char* token = strtok(data, "|");
    config->plugin_name = strdup(token);
    token = strtok(NULL, "|");
    config->config = strdup(token);
}

void load_config(char* blob) {
    PluginConfig config;
    deserialize_config(blob, &config);
    printf("Plugin Name: %s, Config: %s\n", config.plugin_name, config.config);
    free(config.plugin_name);
    free(config.config);
}

int main() {
    char* blob = "text_editor|{\"font\":\"Arial\",\"size\":12}";
    load_config(blob);
    return 0;
}