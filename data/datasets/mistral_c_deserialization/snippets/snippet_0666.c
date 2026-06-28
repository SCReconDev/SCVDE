#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

#define MAX_BUFFER_SIZE 1024

typedef struct {
    char plugin_name[MAX_BUFFER_SIZE];
    char settings[MAX_BUFFER_SIZE];
} PluginSettings;

void load_plugin_settings(const char *json_str, PluginSettings *settings) {
    struct json_object *parsed_json;
    struct json_object *plugin_name_obj;
    struct json_object *settings_obj;

    parsed_json = json_tokener_parse(json_str);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return;
    }

    json_object_object_get_ex(parsed_json, "plugin_name", &plugin_name_obj);
    if (plugin_name_obj != NULL) {
        strncpy(settings->plugin_name, json_object_get_string(plugin_name_obj), MAX_BUFFER_SIZE - 1);
    }

    json_object_object_get_ex(parsed_json, "settings", &settings_obj);
    if (settings_obj != NULL) {
        strncpy(settings->settings, json_object_get_string(settings_obj), MAX_BUFFER_SIZE - 1);
    }

    json_object_put(parsed_json);
}

int main() {
    const char *json_str = "{\"plugin_name\":\"text_editor\",\"settings\":\"font_size=12\"}";
    PluginSettings settings;

    load_plugin_settings(json_str, &settings);

    printf("Plugin Name: %s\n", settings.plugin_name);
    printf("Settings: %s\n", settings.settings);

    return 0;
}