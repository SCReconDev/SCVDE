#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char* plugin_name;
    int enabled;
} PluginConfig;

void deserialize_plugin_config(const char* json_str, PluginConfig* config) {
    struct json_object* parsed_json;
    struct json_object* plugin_name;
    struct json_object* enabled;

    parsed_json = json_tokener_parse(json_str);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return;
    }

    if (json_object_object_get_ex(parsed_json, "plugin_name", &plugin_name)) {
        config->plugin_name = strdup(json_object_get_string(plugin_name));
    }

    if (json_object_object_get_ex(parsed_json, "enabled", &enabled)) {
        config->enabled = json_object_get_int(enabled);
    }

    json_object_put(parsed_json);
}

void process_plugin_config(PluginConfig* config) {
    printf("Plugin Name: %s\n", config->plugin_name);
    printf("Enabled: %d\n", config->enabled);
}

int main() {
    const char* json_str = "{\"plugin_name\":\"security_plugin\",\"enabled\":1}";
    PluginConfig config;

    deserialize_plugin_config(json_str, &config);
    process_plugin_config(&config);

    free(config.plugin_name);
    return 0;
}