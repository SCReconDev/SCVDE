#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* plugin_name;
    int version;
} PluginSettings;

void process_plugin_settings(PluginSettings* settings) {
    printf("Plugin Name: %s\n", settings->plugin_name);
    printf("Version: %d\n", settings->version);
}

void deserialize_plugin_settings(const char* blob, PluginSettings* settings) {
    char* data = strdup(blob);
    char* token = strtok(data, ":");
    settings->plugin_name = strdup(token);
    token = strtok(NULL, ":");
    settings->version = atoi(token);
    free(data);
}

void load_plugin_settings(const char* blob) {
    PluginSettings settings;
    deserialize_plugin_settings(blob, &settings);
    process_plugin_settings(&settings);
}

int main() {
    const char* blob = "analytics:2";
    load_plugin_settings(blob);
    return 0;
}