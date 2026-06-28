#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* plugin_name;
    char* settings;
} Plugin;

Plugin* deserialize_plugin(const char* state) {
    Plugin* plugin = malloc(sizeof(Plugin));
    char* token = strtok((char*)state, ":");
    plugin->plugin_name = strdup(token);
    token = strtok(NULL, ":");
    plugin->settings = strdup(token);
    return plugin;
}

void load_plugin(const char* state) {
    Plugin* plugin = deserialize_plugin(state);
    printf("Plugin: %s\n", plugin->plugin_name);
    free(plugin->plugin_name);
    free(plugin->settings);
    free(plugin);
}

int main() {
    char* state = "logger:enabled=true";
    load_plugin(state);
    return 0;
}