#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

#define MAX_BUFFER_SIZE 1024

typedef struct {
    char plugin_name[MAX_BUFFER_SIZE];
    char plugin_config[MAX_BUFFER_SIZE];
} PluginConfig;

void load_plugin_config(const char* json_data) {
    struct json_object *parsed_json;
    struct json_object *plugin_name_obj, *plugin_config_obj;
    PluginConfig config;

    parsed_json = json_tokener_parse(json_data);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON data\n");
        return;
    }

    if (!json_object_object_get_ex(parsed_json, "plugin_name", &plugin_name_obj) ||
        !json_object_object_get_ex(parsed_json, "plugin_config", &plugin_config_obj)) {
        fprintf(stderr, "Error: Missing required fields in JSON data\n");
        json_object_put(parsed_json);
        return;
    }

    strncpy(config.plugin_name, json_object_get_string(plugin_name_obj), MAX_BUFFER_SIZE - 1);
    strncpy(config.plugin_config, json_object_get_string(plugin_config_obj), MAX_BUFFER_SIZE - 1);

    printf("Plugin Name: %s, Plugin Config: %s\n", config.plugin_name, config.plugin_config);

    json_object_put(parsed_json);
}

int main() {
    const char* json_data = "{\"plugin_name\":\"logger\",\"plugin_config\":\"config_data\"}";
    load_plugin_config(json_data);
    return 0;
}