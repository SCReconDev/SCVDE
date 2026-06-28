#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* plugin;
    int version;
} Plugin;

void deserialize_plugin(Plugin* plugin, const char* data) {
    char* token = strtok((char*)data, ",");
    plugin->plugin = strdup(token);
    token = strtok(NULL, ",");
    plugin->version = atoi(token);
}

void load_config(const char* blob) {
    Plugin plugin;
    deserialize_plugin(&plugin, blob);
    printf("Plugin: %s, Version: %d\n", plugin.plugin, plugin.version);
    free(plugin.plugin);
}

int main() {
    const char* blob = "logger,1.0";
    load_config(blob);
    return 0;
}