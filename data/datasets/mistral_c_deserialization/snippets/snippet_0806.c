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
    struct json_object *plugin_name_obj, *config_obj;

    parsed_json = json_tokener_parse(json_str);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return;
    }

    json_object_object_get_ex(parsed_json, "plugin_name", &plugin_name_obj);
    json_object_object_get_ex(parsed_json, "config", &config_obj);

    if (plugin_name_obj != NULL && json_object_get_type(plugin_name_obj) == json_type_string) {
        config->plugin_name = strdup(json_object_get_string(plugin_name_obj));
    }

    if (config_obj != NULL && json_object_get_type(config_obj) == json_type_string) {
        config->config = strdup(json_object_get_string(config_obj));
    }

    json_object_put(parsed_json);
}

int main() {
    const char *json_str = "{\"plugin_name\":\"logger\",\"config\":\"log_level=debug\"}";
    PluginConfig config;

    deserialize_plugin_config(json_str, &config);

    printf("Plugin Name: %s\n", config.plugin_name);
    printf("Config: %s\n", config.config);

    free(config.plugin_name);
    free(config.config);
    return 0;
}