#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char* plugin_name;
    int plugin_version;
} PluginConfig;

void deserialize_plugin_config(const char* json_str, PluginConfig* config) {
    struct json_object* parsed_json;
    struct json_object* plugin_name;
    struct json_object* plugin_version;

    parsed_json = json_tokener_parse(json_str);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return;
    }

    if (json_object_object_get_ex(parsed_json, "plugin_name", &plugin_name)) {
        config->plugin_name = strdup(json_object_get_string(plugin_name));
    }

    if (json_object_object_get_ex(parsed_json, "plugin_version", &plugin_version)) {
        config->plugin_version = json_object_get_int(plugin_version);
    }

    json_object_put(parsed_json);
}

int main() {
    const char* json_str = "{\"plugin_name\":\"example_plugin\",\"plugin_version\":1}";
    PluginConfig config;

    deserialize_plugin_config(json_str, &config);

    printf("Plugin Name: %s\n", config.plugin_name);
    printf("Plugin Version: %d\n", config.plugin_version);

    free(config.plugin_name);
    return 0;
}