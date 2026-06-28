#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char plugin_name[50];
    char settings[100];
} Plugin;

void load_plugin(const char* config) {
    Plugin* plugin = (Plugin*)malloc(sizeof(Plugin));
    memcpy(plugin, config, sizeof(Plugin));
    printf("Plugin: %s, Settings: %s\n", plugin->plugin_name, plugin->settings);
    free(plugin);
}

int main() {
    char config[200];
    printf("Enter config: ");
    fgets(config, sizeof(config), stdin);
    load_plugin(config);
    return 0;
}