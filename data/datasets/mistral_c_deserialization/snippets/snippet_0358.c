#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char plugin_name[50];
    int version;
} Plugin;

void deserialize_plugin(const char* data, Plugin* plugin) {
    char* decoded_data = malloc(strlen(data) + 1);
    strcpy(decoded_data, data);
    sscanf(decoded_data, "%49s %d", plugin->plugin_name, &plugin->version);
    free(decoded_data);
}

void load_plugin_settings(const char* plugin_data) {
    Plugin plugin;
    deserialize_plugin(plugin_data, &plugin);
    printf("Plugin: %s, Version: %d\n", plugin.plugin_name, plugin.version);
}

int main() {
    const char* plugin_data = "security_plugin 1.0";
    load_plugin_settings(plugin_data);
    return 0;
}