#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* plugin_name;
    int version;
} Plugin;

void deserialize_plugin(char* data, Plugin* plugin) {
    char* token = strtok(data, ":");
    plugin->plugin_name = strdup(token);
    token = strtok(NULL, ":");
    plugin->version = atoi(token);
}

void load_config(char* config_blob) {
    Plugin plugin;
    deserialize_plugin(config_blob, &plugin);
    printf("Plugin: %s, Version: %d\n", plugin.plugin_name, plugin.version);
    free(plugin.plugin_name);
}

int main() {
    char* config_blob = "security:1.0";
    load_config(config_blob);
    return 0;
}