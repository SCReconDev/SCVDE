#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* plugin_name;
    int version;
} Plugin;

void load_plugin(const char* data, Plugin* plugin) {
    char* token = strtok((char*)data, ",");
    plugin->plugin_name = strdup(token);
    token = strtok(NULL, ",");
    plugin->version = atoi(token);
}

int main() {
    char config_data[] = "plugin1,1";
    Plugin plugin;
    load_plugin(config_data, &plugin);

    printf("Plugin Name: %s, Version: %d\n", plugin.plugin_name, plugin.version);
    free(plugin.plugin_name);

    return 0;
}