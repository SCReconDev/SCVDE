#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* plugin_name;
    int version;
} Plugin;

void load_plugin_settings(const char* blob, Plugin* plugin) {
    char* data = strdup(blob);
    char* token = strtok(data, ":");
    plugin->plugin_name = strdup(token);
    token = strtok(NULL, ":");
    plugin->version = atoi(token);
    free(data);
}

int main() {
    char* config_blob = "security_plugin:2";
    Plugin plugin;
    load_plugin_settings(config_blob, &plugin);
    printf("Plugin Name: %s, Version: %d\n", plugin->plugin_name, plugin->version);
    free(plugin.plugin_name);
    return 0;
}