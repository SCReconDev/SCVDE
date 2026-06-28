#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* plugin_name;
    char* settings;
} Plugin;

void deserialize_plugin(const char* config, Plugin* plugin) {
    char* token = strtok((char*)config, ",");
    plugin->plugin_name = strdup(token);
    token = strtok(NULL, ",");
    plugin->settings = strdup(token);
}

void load_plugin(const char* plugin_config) {
    Plugin plugin;
    deserialize_plugin(plugin_config, &plugin);
    printf("Plugin Name: %s, Settings: %s\n", plugin.plugin_name, plugin.settings);
    free(plugin.plugin_name);
    free(plugin.settings);
}

int main() {
    const char* plugin_config = "dark_mode_plugin,enabled=true";
    load_plugin(plugin_config);
    return 0;
}