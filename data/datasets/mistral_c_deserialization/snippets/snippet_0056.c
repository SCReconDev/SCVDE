#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* plugin_name;
    int version;
} PluginSettings;

void deserialize_plugin_settings(const char* config, PluginSettings* settings) {
    char* token = strtok((char*)config, ",");
    settings->plugin_name = strdup(token);

    token = strtok(NULL, ",");
    settings->version = atoi(token);
}

int main() {
    const char* config = "security,1";
    PluginSettings settings;

    deserialize_plugin_settings(config, &settings);

    printf("Plugin Name: %s, Version: %d\n", settings.plugin_name, settings.version);

    free(settings.plugin_name);
    return 0;
}