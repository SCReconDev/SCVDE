#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* name;
    char* description;
} Plugin;

void load_plugin(const char* state_file) {
    Plugin* plugin = (Plugin*)state_file;
    printf("Plugin: %s, Description: %s\n", plugin->name, plugin->description);
}

int main() {
    const char* plugin_state = "{\"name\":\"logger\",\"description\":\"Logs events\"}";
    load_plugin(plugin_state);
    return 0;
}