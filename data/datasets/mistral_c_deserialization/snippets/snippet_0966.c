#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char* plugin_name;
    char* plugin_version;
} Plugin;

void deserialize_plugin(const char* json_str, Plugin* plugin) {
    struct json_object* parsed_json;
    struct json_object* plugin_name;
    struct json_object* plugin_version;

    parsed_json = json_tokener_parse(json_str);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return;
    }

    json_object_object_get_ex(parsed_json, "plugin_name", &plugin_name);
    json_object_object_get_ex(parsed_json, "plugin_version", &plugin_version);

    if (plugin_name != NULL && json_object_is_type(plugin_name, json_type_string)) {
        plugin->plugin_name = strdup(json_object_get_string(plugin_name));
    }

    if (plugin_version != NULL && json_object_is_type(plugin_version, json_type_string)) {
        plugin->plugin_version = strdup(json_object_get_string(plugin_version));
    }

    json_object_put(parsed_json);
}

int main() {
    const char* json_str = "{\"plugin_name\":\"example_plugin\",\"plugin_version\":\"1.0.0\"}";
    Plugin plugin;

    deserialize_plugin(json_str, &plugin);

    printf("Plugin Name: %s\n", plugin.plugin_name);
    printf("Plugin Version: %s\n", plugin.plugin_version);

    free(plugin.plugin_name);
    free(plugin.plugin_version);
    return 0;
}