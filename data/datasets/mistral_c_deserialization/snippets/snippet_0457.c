#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[50];
    int version;
} Plugin;

void deserialize_plugin(char* data, Plugin* plugin) {
    char* token = strtok(data, ",");
    strcpy(plugin->name, token);
    token = strtok(NULL, ",");
    plugin->version = atoi(token);
}

void import_plugin(char* state_file) {
    Plugin plugin;
    deserialize_plugin(state_file, &plugin);
    printf("Imported plugin: %s, version %d\n", plugin.name, plugin.version);
}

int main() {
    char state_file[] = "my_plugin,1";
    import_plugin(state_file);
    return 0;
}