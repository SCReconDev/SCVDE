#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char *plugin_name;
    char *settings;
} PluginSettings;

void parse_plugin_settings(const char *json_str) {
    struct json_object *parsed_json;
    struct json_object *plugin_name;
    struct json_object *settings;

    parsed_json = json_tokener_parse(json_str);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return;
    }

    if (!json_object_object_get_ex(parsed_json, "plugin_name", &plugin_name)) {
        fprintf(stderr, "Plugin name not found in JSON\n");
        json_object_put(parsed_json);
        return;
    }

    if (!json_object_object_get_ex(parsed_json, "settings", &settings)) {
        fprintf(stderr, "Settings not found in JSON\n");
        json_object_put(parsed_json);
        return;
    }

    PluginSettings plugin_settings;
    plugin_settings.plugin_name = strdup(json_object_get_string(plugin_name));
    plugin_settings.settings = strdup(json_object_get_string(settings));

    printf("Plugin Name: %s, Settings: %s\n", plugin_settings.plugin_name, plugin_settings.settings);

    free(plugin_settings.plugin_name);
    free(plugin_settings.settings);
    json_object_put(parsed_json);
}

int main() {
    const char *json_str = "{\"plugin_name\":\"theme_plugin\",\"settings\":\"{\\\"theme\\\":\\\"dark\\\"}\"}";
    parse_plugin_settings(json_str);
    return 0;
}