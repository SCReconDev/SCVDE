#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char plugin_name[50];
    int version;
} Plugin;

void load_config(char* config_blob) {
    Plugin* plugin = (Plugin*)malloc(sizeof(Plugin));
    memcpy(plugin, config_blob, sizeof(Plugin));
    printf("Plugin loaded: %s (Version: %d)\n", plugin->plugin_name, plugin->version);
    free(plugin);
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Usage: %s <config_blob>\n", argv[0]);
        return 1;
    }

    char* config_blob = argv[1];
    load_config(config_blob);

    return 0;
}