#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* plugin_name;
    int version;
} Plugin;

void load_plugin(char* state_file) {
    Plugin* plugin = (Plugin*)malloc(sizeof(Plugin));
    memcpy(plugin, state_file, sizeof(Plugin));
    printf("Plugin: %s, Version: %d\n", plugin->plugin_name, plugin->version);
    free(plugin);
}

int main(int argc, char** argv) {
    if (argc < 2) {
        printf("Usage: %s <state_file>\n", argv[0]);
        return 1;
    }
    load_plugin(argv[1]);
    return 0;
}