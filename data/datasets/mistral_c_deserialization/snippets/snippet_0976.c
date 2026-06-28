#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char* plugin_name;
    int version;
} PluginSettings;

void deserialize_plugin_settings(const char* json_str, PluginSettings* settings) {
    struct json_object* parsed_json;
    struct json_object* plugin_name;
    struct json_object* version;

    parsed_json = json_tokener_parse(json_str);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return;
    }

    if (!json_object_object_get_ex(parsed_json, "plugin_name", &plugin_name)) {
        fprintf(stderr, "Error: 'plugin_name' field not found\n");
        json_object_put(parsed_json);
        return;
    }

    if (!json_object_object_get_ex(parsed_json, "version", &version)) {
        fprintf(stderr, "Error: 'version' field not found\n");
        json_object_put(parsed_json);
        return;
    }

    settings->plugin_name = strdup(json_object_get_string(plugin_name));
    settings->version = json_object_get_int(version);

    json_object_put(parsed_json);
}

int main() {
    const char* json_str = "{\"plugin_name\":\"example_plugin\",\"version\":1}";
    PluginSettings settings;

    deserialize_plugin_settings(json_str, &settings);

    printf("Plugin Name: %s\n", settings.plugin_name);
    printf("Version: %d\n", settings.version);

    free(settings.plugin_name);
    return 0;
}