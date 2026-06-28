#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char* plugin_name;
    char* plugin_config;
} PluginConfig;

void deserialize_plugin_config(const char* json_str, PluginConfig* plugin_config) {
    struct json_object* parsed_json;
    struct json_object* plugin_name_obj;
    struct json_object* plugin_config_obj;

    parsed_json = json_tokener_parse(json_str);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return;
    }

    if (!json_object_object_get_ex(parsed_json, "plugin_name", &plugin_name_obj)) {
        fprintf(stderr, "Error getting plugin_name from JSON\n");
        json_object_put(parsed_json);
        return;
    }

    if (!json_object_object_get_ex(parsed_json, "plugin_config", &plugin_config_obj)) {
        fprintf(stderr, "Error getting plugin_config from JSON\n");
        json_object_put(parsed_json);
        return;
    }

    plugin_config->plugin_name = strdup(json_object_get_string(plugin_name_obj));
    plugin_config->plugin_config = strdup(json_object_get_string(plugin_config_obj));

    json_object_put(parsed_json);
}

int main() {
    const char* json_str = "{\"plugin_name\":\"example_plugin\",\"plugin_config\":\"config_value=123\"}";
    PluginConfig plugin_config;

    deserialize_plugin_config(json_str, &plugin_config);

    printf("Plugin Name: %s\n", plugin_config.plugin_name);
    printf("Plugin Config: %s\n", plugin_config.plugin_config);

    free(plugin_config.plugin_name);
    free(plugin_config.plugin_config);

    return 0;
}