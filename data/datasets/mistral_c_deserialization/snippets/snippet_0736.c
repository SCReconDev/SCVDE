#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    char plugin_name[50];
    char plugin_version[20];
    char plugin_config[200];
} Plugin;

bool validate_plugin(Plugin* plugin) {
    if (strlen(plugin->plugin_name) == 0 || strlen(plugin->plugin_version) == 0 || strlen(plugin->plugin_config) == 0) {
        return false;
    }
    return true;
}

void load_plugin(Plugin* plugin) {
    if (validate_plugin(plugin)) {
        printf("Plugin loaded: %s, %s, %s\n", plugin->plugin_name, plugin->plugin_version, plugin->plugin_config);
    } else {
        printf("Invalid plugin data\n");
    }
}

int main() {
    Plugin plugin1 = {"example_plugin", "1.0.0", "{\"setting1\": \"value1\", \"setting2\": \"value2\"}"};
    Plugin plugin2 = {"", "1.0.0", "{\"setting1\": \"value1\", \"setting2\": \"value2\"}"};

    load_plugin(&plugin1);
    load_plugin(&plugin2);

    return 0;
}