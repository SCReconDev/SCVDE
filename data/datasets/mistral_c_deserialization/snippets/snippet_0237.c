#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* name;
    char* description;
} Plugin;

void deserialize_plugin(Plugin* plugin, const char* data) {
    char* token = strtok((char*)data, "~");
    plugin->name = strdup(token);
    token = strtok(NULL, "~");
    plugin->description = strdup(token);
}

int main() {
    FILE* file = fopen("plugin_data.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    char buffer[1024];
    if (fgets(buffer, sizeof(buffer), file) == NULL) {
        perror("Error reading file");
        fclose(file);
        return 1;
    }

    Plugin plugin;
    deserialize_plugin(&plugin, buffer);

    printf("Name: %s, Description: %s\n", plugin.name, plugin.description);

    free(plugin.name);
    free(plugin.description);
    fclose(file);
    return 0;
}