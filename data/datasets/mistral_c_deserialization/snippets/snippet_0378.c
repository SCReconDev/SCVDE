#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* plugin_name;
    int version;
} Plugin;

void load_plugin_config(const char* config) {
    Plugin plugin;
    char* decoded = strdup(config);
    char* token = strtok(decoded, ";");
    plugin.plugin_name = strdup(token);
    token = strtok(NULL, ";");
    plugin.version = atoi(token);
    printf("Plugin loaded: %s v%d\n", plugin.plugin_name, plugin.version);
    free(plugin.plugin_name);
    free(decoded);
}

int main() {
    const char* config = "audio_player;2";
    load_plugin_config(config);
    return 0;
}