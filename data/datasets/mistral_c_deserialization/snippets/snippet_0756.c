#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char *plugin_name;
    char *config;
} PluginConfig;

void deserialize_plugin_config(const char *json_str, PluginConfig *config) {
    struct json_object *parsed_json;
    struct json_object *plugin_name;
    struct json_object *config_data;

    parsed_json = json_tokener_parse(json_str);

    if (json_object_object_get_ex(parsed_json, "plugin_name", &plugin_name)) {
        config->plugin_name = strdup(json_object_get_string(plugin_name));
    }

    if (json_object_object_get_ex(parsed_json, "config", &config_data)) {
        config->config = strdup(json_object_get_string(config_data));
    }

    json_object_put(parsed_json);
}

int main() {
    const char *json_str = "{\"plugin_name\":\"example_plugin\",\"config\":\"{\\\"setting\\\":\\\"value\\\"}\"}";
    PluginConfig config;

    deserialize_plugin_config(json_str, &config);

    printf("Plugin Name: %s\n", config.plugin_name);
    printf("Config: %s\n", config.config);

    free(config.plugin_name);
    free(config.config);

    return 0;
}