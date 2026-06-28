#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* name;
    int version;
} Plugin;

void deserialize_plugin(char* data, Plugin* plugin) {
    char* token = strtok(data, ",");
    plugin->name = strdup(token);
    token = strtok(NULL, ",");
    plugin->version = atoi(token);
}

void import_file(char* state_file) {
    FILE* file = fopen(state_file, "r");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }
    char buffer[1024];
    fgets(buffer, sizeof(buffer), file);
    Plugin plugin;
    deserialize_plugin(buffer, &plugin);
    printf("Plugin Name: %s, Version: %d\n", plugin.name, plugin.version);
    free(plugin.name);
    fclose(file);
}

int main() {
    char* state_file = "plugin_state.txt";
    import_file(state_file);
    return 0;
}