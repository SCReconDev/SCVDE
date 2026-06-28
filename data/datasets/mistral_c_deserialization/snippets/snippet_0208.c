#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char plugin_name[50];
    int version;
} PluginSettings;

void unsafe_deserialize(PluginSettings *settings, const char *data) {
    sscanf(data, "%49s %d", settings->plugin_name, &settings->version);
}

void load_plugin_settings(const char *blob) {
    PluginSettings settings;
    unsafe_deserialize(&settings, blob);
    printf("Plugin Settings: %s, Version: %d\n", settings.plugin_name, settings.version);
}

int main() {
    char blob[100];
    printf("Enter plugin settings blob: ");
    fgets(blob, sizeof(blob), stdin);
    load_plugin_settings(blob);
    return 0;
}