#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* name;
    int version;
} Plugin;

void load_plugin(Plugin* plugin, const char* state) {
    char* token = strtok((char*)state, ";");
    plugin->name = strdup(token);
    token = strtok(NULL, ";");
    plugin->version = atoi(token);
}

int main() {
    const char* state = "my_plugin;1";
    Plugin plugin;
    load_plugin(&plugin, state);
    printf("Name: %s, Version: %d\n", plugin.name, plugin.version);
    free(plugin.name);
    return 0;
}