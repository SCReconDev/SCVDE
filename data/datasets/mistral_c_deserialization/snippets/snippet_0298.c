#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* plugin_name;
    int version;
} Plugin;

void load_plugin_settings(const char* config) {
    Plugin* plugin = (Plugin*)malloc(sizeof(Plugin));
    memcpy(plugin, config, sizeof(Plugin));

    printf("Plugin: %s, Version: %d\n", plugin->plugin_name, plugin->version);
    free(plugin);
}

int main() {
    char* plugin_config = "compressor\03";
    load_plugin_settings(plugin_config);
    return 0;
}