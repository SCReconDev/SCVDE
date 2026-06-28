#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* plugin_name;
    int version;
} PluginSettings;

void deserialize_plugin_settings(PluginSettings* settings, const char* data) {
    char* token = strtok((char*)data, "-");
    settings->plugin_name = strdup(token);
    token = strtok(NULL, "-");
    settings->version = atoi(token);
}

void load_plugin_settings(const char* config_blob) {
    PluginSettings settings;
    deserialize_plugin_settings(&settings, config_blob);
    printf("Plugin Settings - Name: %s, Version: %d\n", settings.plugin_name, settings.version);
    free(settings.plugin_name);
}

int main() {
    const char* config_blob = "security_plugin-2";
    load_plugin_settings(config_blob);
    return 0;
}