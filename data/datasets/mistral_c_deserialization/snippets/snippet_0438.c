#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* plugin_name;
    char* settings;
} PluginConfig;

void load_plugin(PluginConfig* config) {
    printf("Loading plugin: %s, Settings: %s\n", config->plugin_name, config->settings);
}

int main() {
    char* config_blob = "{\"plugin_name\":\"logger\",\"settings\":\"verbose\"}";
    PluginConfig* config = (PluginConfig*)malloc(sizeof(PluginConfig));
    memcpy(config, config_blob, sizeof(PluginConfig));
    load_plugin(config);
    free(config);
    return 0;
}