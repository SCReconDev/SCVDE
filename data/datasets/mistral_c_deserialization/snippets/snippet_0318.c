#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* plugin_name;
    int version;
    char* settings;
} Plugin;

void load_plugin(const char* data, Plugin* plugin) {
    char* token = strtok((char*)data, "-");
    plugin->plugin_name = strdup(token);
    token = strtok(NULL, "-");
    plugin->version = atoi(token);
    token = strtok(NULL, "-");
    plugin->settings = strdup(token);
}

int main() {
    char* plugin_data = "image_processor-1.0-{resize: true, quality: 80}";
    Plugin plugin;
    load_plugin(plugin_data, &plugin);
    printf("Plugin Name: %s, Version: %d, Settings: %s\n", plugin.plugin_name, plugin.version, plugin.settings);
    free(plugin.plugin_name);
    free(plugin.settings);
    return 0;
}