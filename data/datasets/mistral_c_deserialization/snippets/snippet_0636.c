#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <cjson/cJSON.h>

typedef struct {
    char* plugin_name;
    char* version;
    int settings_count;
    char** settings;
} Plugin;

bool validate_plugin_schema(cJSON* json) {
    if (!cJSON_HasObjectItem(json, "plugin_name") ||
        !cJSON_HasObjectItem(json, "version") ||
        !cJSON_HasObjectItem(json, "settings")) {
        return false;
    }

    cJSON* plugin_name = cJSON_GetObjectItemCaseSensitive(json, "plugin_name");
    cJSON* version = cJSON_GetObjectItemCaseSensitive(json, "version");
    cJSON* settings = cJSON_GetObjectItemCaseSensitive(json, "settings");

    if (!cJSON_IsString(plugin_name) || !cJSON_IsString(version) || !cJSON_IsArray(settings)) {
        return false;
    }

    return true;
}

Plugin* deserialize_plugin(const char* json_str) {
    cJSON* json = cJSON_Parse(json_str);
    if (!json) {
        return NULL;
    }

    if (!validate_plugin_schema(json)) {
        cJSON_Delete(json);
        return NULL;
    }

    Plugin* plugin = (Plugin*)malloc(sizeof(Plugin));
    if (!plugin) {
        cJSON_Delete(json);
        return NULL;
    }

    cJSON* plugin_name = cJSON_GetObjectItemCaseSensitive(json, "plugin_name");
    cJSON* version = cJSON_GetObjectItemCaseSensitive(json, "version");
    cJSON* settings = cJSON_GetObjectItemCaseSensitive(json, "settings");

    plugin->plugin_name = strdup(plugin_name->valuestring);
    plugin->version = strdup(version->valuestring);
    plugin->settings_count = cJSON_GetArraySize(settings);
    plugin->settings = (char**)malloc(plugin->settings_count * sizeof(char*));

    for (int i = 0; i < plugin->settings_count; i++) {
        cJSON* setting = cJSON_GetArrayItem(settings, i);
        if (cJSON_IsString(setting)) {
            plugin->settings[i] = strdup(setting->valuestring);
        } else {
            plugin->settings[i] = NULL;
        }
    }

    cJSON_Delete(json);

    return plugin;
}

void free_plugin(Plugin* plugin) {
    if (plugin) {
        free(plugin->plugin_name);
        free(plugin->version);
        for (int i = 0; i < plugin->settings_count; i++) {
            free(plugin->settings[i]);
        }
        free(plugin->settings);
        free(plugin);
    }
}

int main() {
    const char* json_str = "{\"plugin_name\":\"example_plugin\",\"version\":\"1.0\",\"settings\":[\"setting1\",\"setting2\"]}";
    Plugin* plugin = deserialize_plugin(json_str);

    if (plugin) {
        printf("Plugin Name: %s\n", plugin->plugin_name);
        printf("Version: %s\n", plugin->version);
        printf("Settings:\n");
        for (int i = 0; i < plugin->settings_count; i++) {
            printf("  %s\n", plugin->settings[i]);
        }
        free_plugin(plugin);
    } else {
        printf("Failed to deserialize plugin.\n");
    }

    return 0;
}