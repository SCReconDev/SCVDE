#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* plugin_name;
    int version;
} Plugin;

void load_plugin(const char* config, Plugin* plugin) {
    char* token = strtok((char*)config, ":");
    plugin->plugin_name = strdup(token);
    token = strtok(NULL, ":");
    plugin->version = atoi(token);
}

int main() {
    char* plugin_config = "security_plugin:2";
    Plugin plugin;
    load_plugin(plugin_config, &plugin);
    printf("Plugin Name: %s, Version: %d\n", plugin.plugin_name, plugin.version);
    free(plugin.plugin_name);
    return 0;
}