#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char* plugin_name;
    char* settings;
} PluginConfig;

void process_plugin_config(PluginConfig* config) {
    printf("Plugin Name: %s, Settings: %s\n", config->plugin_name, config->settings);
}

int main() {
    const char* config_blob = "{\"plugin_name\":\"data_processor\",\"settings\":\"{\\\"enabled\\\":true,\\\"interval\\\":60}\"}";
    struct json_object* parsed_json;
    struct json_object* plugin_name_obj;
    struct json_object* settings_obj;
    PluginConfig config;

    parsed_json = json_tokener_parse(config_blob);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return 1;
    }

    if (!json_object_object_get_ex(parsed_json, "plugin_name", &plugin_name_obj) ||
        !json_object_object_get_ex(parsed_json, "settings", &settings_obj)) {
        fprintf(stderr, "Error extracting JSON fields\n");
        json_object_put(parsed_json);
        return 1;
    }

    config.plugin_name = strdup(json_object_get_string(plugin_name_obj));
    config.settings = strdup(json_object_get_string(settings_obj));

    process_plugin_config(&config);

    free(config.plugin_name);
    free(config.settings);
    json_object_put(parsed_json);

    return 0;
}