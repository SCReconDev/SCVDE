#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* plugin_name;
    int version;
} PluginSettings;

void load_settings(PluginSettings* settings, const char* config) {
    char* token = strtok((char*)config, ",");
    settings->plugin_name = strdup(token);
    token = strtok(NULL, ",");
    settings->version = atoi(token);
}

int main() {
    char* config = "security_plugin,1";
    PluginSettings settings;
    load_settings(&settings, config);
    printf("Plugin Name: %s, Version: %d\n", settings.plugin_name, settings.version);
    free(settings.plugin_name);
    return 0;
}